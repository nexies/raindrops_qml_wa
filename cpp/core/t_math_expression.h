#ifndef T_MATH_EXPRESSION_H
#define T_MATH_EXPRESSION_H

#include <QString>
#include <QVector>
#include <QSet>
#include <QMap>
// #include "typedef.h"
#include <math.h>

enum T_Token_Types{
    start,
    number,
    identificator,
    binary_operator,
    unary_operator,
    open_bracket,
    close_bracket,
    end
};
class T_Token{
public:
    QString str;
    T_Token_Types type;
};

#define foot ( (double) 0,3048 )
#define feet foot

#define NM2M        ( (double) 1852 )          // 1 морская миля = 1852 метра
#define foot2M      ( (double) 0.3048 )        // 1 фут = 0.3048
#define feet2M      foot                       // множественное число
#define FL2M        ( (double) feet*100 )      // 1 Flight Level = 100 футов
#define MINUTE2S    ( (double) 60 )
#define HOUR2S      ( (double) 60 * MINUTE2S )
#define DAY2S       ( (double) 24 * HOUR2S )
#define KM2M        ( (double) 1000 )
#define DEG2RAD     ( (double) M_PI/180 )

namespace baseUnit {
    enum baseUnit{
        kg,   // килограмм
        m,    // метр
        s,    // секунда
        A,    // Ампер
        C,    // Цельсий
        mol,  // моль
        cd,   // канделла
        rad,  // радиан
        dBm,  // уровень в децибелах относительно сигнала в один милливатт
        dB,   // уровень в децибелах
        bar,  // единица измерения давления
        Pa,   // Паскаль
        mach, // скорость звука в среде
        Hz,   // Герц
        count // общее количество элементов
    };
    const QString indToString[count] = {
        "kg",   // килограмм
        "m",    // метр
        "s",    // секунда
        "A",    // Ампер
        "C",    // Цельсий
        "mol",  // моль
        "cd",   // канделла
        "rad",  // радиан
        "dBm",  // уровень в децибелах относительно сигнала в один милливатт
        "dB",   // уровень в децибелах
        "bar",  // бар
        "Pa",   // Паскаль
        "mach", // мах
        "Hz"    // Герц
    };
}

// m, s, rad
struct TUnitsConverter {
public:
    double coef;
    baseUnit::baseUnit baseUnitInd;
public:
    TUnitsConverter(double p_coef, baseUnit::baseUnit p_ind) {coef = p_coef; baseUnitInd = p_ind; }
};

class SI_Units{
public:
    int unit[baseUnit::count]; // содержит степени единиц измерения
public:
    SI_Units(){ // конструктор инициализирует все степени единиц измерений нулями
        for (int i=0; i<baseUnit::count; i++){
            unit[i] =0;
        }
    }
    QString toString(){
        QString numStr="", denomStr="";
        uint numCnt=0, denomCnt=0;
        for (int i=0; i<baseUnit::count; i++){
            if (unit[i] > 0){
                numCnt++;
                if (numStr != "")
                    numStr += "*";
                if (unit[i] == 1){
                    numStr += baseUnit::indToString[i];
                }
                else{
                    numStr += baseUnit::indToString[i]+ "^" + QString::number(unit[i]);
                }
            }
            if (unit[i] < 0){
                denomCnt++;
                if (denomStr != "")
                    denomStr += "*";
                if (unit[i] == -1){
                    denomStr += baseUnit::indToString[i];
                }
                else{
                    denomStr += baseUnit::indToString[i]+ "^" + QString::number(-unit[i]);
                }
            }
        }
        if ((numCnt == 0)&&(denomCnt > 0))
            numStr = "1";
        if (denomCnt > 1)
            denomStr = "(" + denomStr + ")";
        if (denomCnt == 0)
            return numStr;

        return numStr + "/" + denomStr;
    }
};

SI_Units operator*(const SI_Units &p_o1, const SI_Units &p_o2);
SI_Units operator/(const SI_Units &p_o1, const SI_Units &p_o2);
bool operator==(const SI_Units &p_o1, const SI_Units &p_o2);
bool operator!=(const SI_Units &p_o1, const SI_Units &p_o2);

class T_Math_Expression{

private:
    QMap <QChar, uint32_t> priority_operator_set; // задание приоритетов операций включая скобки (скобки имеют самый низкий приоритет)
    QSet <QChar> binary_operator_set;             // перечисление всех допустимых бинарных операций
    QSet <QChar> unary_operator_set;              // = {'+', '-'}; // перечисление всех допустимых унарных операций
    QSet <QChar> abc;                             // перечисление всех допустимых символов в идентификаторе
    QMap <QString, TUnitsConverter*> metric_set;            // таблица пересчета единиц измерения в СИ

    QVector <T_Token> tokens;
    QVector <T_Token> RPN_tokens;

    QString  err_str;              // текстовое описание ошибки
    uint32_t err_id;               // идентификатор ошибки
public:
    QString str;

protected:
    // функция разюиения строки на лексемы
    uint32_t string_to_tokens(const QString &p_str,
                              QVector <T_Token> &p_tokens,
                              QString &p_err_str);

    // функция приведения выражения к обратной польской нотации (записи)
    uint32_t IN2RPN(const QVector <T_Token> &in_tokens,
                    QVector <T_Token>  &out_tokens);

    // Удаление пробелом в выражении
    QString despacing(const QString &p_str);

    //Вычисление выражения, записанного в обратной польской нотации
    double RPN_Evaluate(const QVector <T_Token> &in_tokens, QString &p_err_str, QString & p_units);

    //Вычисление размерсноти выражения, записанного в обратной польской нотации
    QString RPN_unitsEvaluate(const QVector <T_Token> &in_tokens, QString &p_err_str);

public:
    double evaluate (QString &p_err_str, QString & p_unit);
    double evaluate ();

    T_Math_Expression(const QString &p_str);
    T_Math_Expression();
};

#endif // T_MATH_EXPRESSION_H
