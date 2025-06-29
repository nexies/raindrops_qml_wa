#include "t_math_expression.h"
#include <QString>
#include <QVector>
#include <QSet>
#include <QMap>


namespace
{
}


SI_Units operator*(const SI_Units &p_o1, const SI_Units &p_o2){
    SI_Units res;
    for (int i=0; i<baseUnit::count; i++){
        res.unit[i] = p_o1.unit[i]+p_o2.unit[i];
    }
    return res;
}

SI_Units operator/(const SI_Units &p_o1, const SI_Units &p_o2){
    SI_Units res;
    for (int i=0; i<baseUnit::count; i++){
        res.unit[i] = p_o1.unit[i]-p_o2.unit[i];
    }
    return res;
}
bool operator==(const SI_Units &p_o1, const SI_Units &p_o2){
    for (int i=0; i<baseUnit::count; i++){
        if (p_o1.unit[i] != p_o2.unit[i])
           return false;
    }
    return true;
}
bool operator!=(const SI_Units &p_o1, const SI_Units &p_o2){
    return !(operator==(p_o1, p_o2));
}
SI_Units pow(const SI_Units &p_o1 , const double degree){
    SI_Units res;
    for (int i=0; i<baseUnit::count; i++){
        res.unit[i] = p_o1.unit[i] * degree;
    }
    return res;
}
//------------------------------------------------------------------------------------------------
// Конструктор с инициализацией математическим выражением
//------------------------------------------------------------------------------------------------
T_Math_Expression::T_Math_Expression(const QString &p_str)
{
    str = p_str;

    priority_operator_set.insert('+', 1);
    priority_operator_set.insert('-', 1);
    priority_operator_set.insert('*', 2);
    priority_operator_set.insert('/', 2);
    priority_operator_set.insert('^', 3);
    priority_operator_set.insert('(', 0);
    priority_operator_set.insert(')', 0);
    binary_operator_set << '+' << '-' << '*' << '/'<< '^';
    unary_operator_set << '+' << '-';
    abc <<'a'<<'b'<<'c'<<'d'<<'e'<<'f'<<'g'<<'h'<<'i'<<'j'<<'k'<<'l'<<'m'<<'n'<<'o'<<'p'<<'q'<<'r'<<'s'<<'t'<<'u'<<'v'<<'w'<<'x'<<'y'<<'z'
        <<'A'<<'B'<<'C'<<'D'<<'E'<<'F'<<'G'<<'H'<<'I'<<'J'<<'K'<<'L'<<'M'<<'N'<<'O'<<'P'<<'Q'<<'R'<<'S'<<'T'<<'U'<<'V'<<'W'<<'X'<<'Y'<<'Z'<<'_';
    metric_set.insert("NM", new TUnitsConverter (NM2M, baseUnit::m));       // морская миля -> метры
    metric_set.insert("nm", new TUnitsConverter (NM2M, baseUnit::m));       // морская миля -> метры
    metric_set.insert("nmi", new TUnitsConverter (NM2M, baseUnit::m));      // морская миля -> метры
    metric_set.insert("ft", new TUnitsConverter (foot2M, baseUnit::m));     //         футы -> метры
    metric_set.insert("FL", new TUnitsConverter (FL2M, baseUnit::m));       // FLIGHT LEVEL -> метры
    metric_set.insert("km", new TUnitsConverter (KM2M, baseUnit::m));       //    километры -> метры
    metric_set.insert("m", new TUnitsConverter (1, baseUnit::m));           //        метры -> метры
    metric_set.insert("hour", new TUnitsConverter (HOUR2S, baseUnit::s));   //         часы -> секунды
    metric_set.insert("min", new TUnitsConverter (MINUTE2S, baseUnit::s));  //       минуты -> секунды
    metric_set.insert("s", new TUnitsConverter (1, baseUnit::s));           //      секунды -> секунды
    metric_set.insert("ms", new TUnitsConverter (0.001, baseUnit::s));      //  милисекунды -> секунды
    metric_set.insert("deg", new TUnitsConverter (DEG2RAD, baseUnit::rad)); //      градусы -> радианы
    metric_set.insert("rad", new TUnitsConverter (1, baseUnit::rad));       //      радианы -> радианы
    metric_set.insert("dBm", new TUnitsConverter (1, baseUnit::dBm));       //    Децибеллы -> Децибеллы
    metric_set.insert("dB", new TUnitsConverter (1, baseUnit::dB));         //    Децибеллы -> Децибеллы
    metric_set.insert("C", new TUnitsConverter (1, baseUnit::C));           //      Цельсий -> Цельсий
    metric_set.insert("bar", new TUnitsConverter (1, baseUnit::bar));       //          Бар -> Бар
    metric_set.insert("mbar", new TUnitsConverter (0.001, baseUnit::bar));  //     миллибар -> Бар
    metric_set.insert("Pa", new TUnitsConverter (1, baseUnit::Pa));         //      Паскаль -> Паскаль
    metric_set.insert("hPa", new TUnitsConverter (100, baseUnit::Pa));      // Гектопаскаль -> Паскаль
    metric_set.insert("Hz", new TUnitsConverter (1, baseUnit::Hz));         //         Герц -> Герц
    metric_set.insert("KHz", new TUnitsConverter (1e3, baseUnit::Hz));      //         Герц -> Килогерц
    metric_set.insert("MHz", new TUnitsConverter (1e6, baseUnit::Hz));      //         Герц -> Мегагерц
    metric_set.insert("mach", new TUnitsConverter (1, baseUnit::mach));     //          мах -> мах
}

//------------------------------------------------------------------------------------------------
// Тривиальный конструктор
//------------------------------------------------------------------------------------------------
T_Math_Expression::T_Math_Expression()
{
    str = "";
    priority_operator_set.insert('+', 1);
    priority_operator_set.insert('-', 1);
    priority_operator_set.insert('*', 2);
    priority_operator_set.insert('/', 2);
    priority_operator_set.insert('^', 3);
    priority_operator_set.insert('(', 0);
    priority_operator_set.insert(')', 0);
    binary_operator_set << '+' << '-' << '*' << '/'<< '^';
    unary_operator_set << '+' << '-';
    abc <<'a'<<'b'<<'c'<<'d'<<'e'<<'f'<<'g'<<'h'<<'i'<<'j'<<'k'<<'l'<<'m'<<'n'<<'o'<<'p'<<'q'<<'r'<<'s'<<'t'<<'u'<<'v'<<'w'<<'x'<<'y'<<'z'
        <<'A'<<'B'<<'C'<<'D'<<'E'<<'F'<<'G'<<'H'<<'I'<<'J'<<'K'<<'L'<<'M'<<'N'<<'O'<<'P'<<'Q'<<'R'<<'S'<<'T'<<'U'<<'V'<<'W'<<'X'<<'Y'<<'Z'<<'_';
    metric_set.insert("NM", new TUnitsConverter (NM2M, baseUnit::m));       // морская миля -> метры
    metric_set.insert("nm", new TUnitsConverter (NM2M, baseUnit::m));       // морская миля -> метры
    metric_set.insert("nmi", new TUnitsConverter (NM2M, baseUnit::m));      // морская миля -> метры
    metric_set.insert("ft", new TUnitsConverter (foot2M, baseUnit::m));     //         футы -> метры
    metric_set.insert("FL", new TUnitsConverter (FL2M, baseUnit::m));       // FLIGHT LEVEL -> метры
    metric_set.insert("km", new TUnitsConverter (KM2M, baseUnit::m));       //    километры -> метры
    metric_set.insert("m", new TUnitsConverter (1, baseUnit::m));           //        метры -> метры
    metric_set.insert("hour", new TUnitsConverter (HOUR2S, baseUnit::s));   //         часы -> секунды
    metric_set.insert("min", new TUnitsConverter (MINUTE2S, baseUnit::s));  //       минуты -> секунды
    metric_set.insert("s", new TUnitsConverter (1, baseUnit::s));           //      секунды -> секунды
    metric_set.insert("ms", new TUnitsConverter (0.001, baseUnit::s));      //  милисекунды -> секунды
    metric_set.insert("deg", new TUnitsConverter (DEG2RAD, baseUnit::rad)); //      градусы -> радианы
    metric_set.insert("rad", new TUnitsConverter (1, baseUnit::rad));       //      радианы -> радианы
    metric_set.insert("dBm", new TUnitsConverter (1, baseUnit::dBm));       //    Децибеллы -> Децибеллы
    metric_set.insert("dB", new TUnitsConverter (1, baseUnit::dB));         //    Децибеллы -> Децибеллы
    metric_set.insert("C", new TUnitsConverter (1, baseUnit::C));           //      Цельсий -> Цельсий
    metric_set.insert("bar", new TUnitsConverter (1, baseUnit::bar));       //          Бар -> Бар
    metric_set.insert("mbar", new TUnitsConverter (0.001, baseUnit::bar));  //     миллибар -> Бар
    metric_set.insert("Pa", new TUnitsConverter (1, baseUnit::Pa));         //      Паскаль -> Паскаль
    metric_set.insert("hPa", new TUnitsConverter (100, baseUnit::Pa));      // Гектопаскаль -> Паскаль
    metric_set.insert("Hz", new TUnitsConverter (1, baseUnit::Hz));         //         Герц -> Герц
    metric_set.insert("KHz", new TUnitsConverter (1e3, baseUnit::Hz));      //         Герц -> Килогерц
    metric_set.insert("MHz", new TUnitsConverter (1e6, baseUnit::Hz));      //         Герц -> Мегагерц
    metric_set.insert("mach", new TUnitsConverter (1, baseUnit::mach));     //          мах -> мах
}

//------------------------------------------------------------------------------------------------
// Вычисление значения математического выражения
//------------------------------------------------------------------------------------------------
double T_Math_Expression::evaluate (QString &p_err_str, QString &p_unit)
{
    //   if (str.isEmpty()){
    //        return 0;
    //    }
    p_err_str.clear();
    if (string_to_tokens(str, tokens, p_err_str)){
        return 0;
    }
    if (IN2RPN(tokens, RPN_tokens)){
        return 0;
    }
    return RPN_Evaluate(RPN_tokens, p_err_str, p_unit);
}

double T_Math_Expression::evaluate ()
{
    QString p_err_str, p_unit;
    return evaluate(p_err_str, p_unit);
}

//------------------------------------------------------------------------------------------------
// Приведение математического выражения к обратной польской нотации
//------------------------------------------------------------------------------------------------
uint32_t T_Math_Expression::IN2RPN(const QVector <T_Token> &in_tokens,
                                         QVector <T_Token>  &out_tokens){
    uint32_t loc_err = 0;
    QVector <T_Token> loc_stack;
    //uint32_t loc_priority = UINT32_MAX;
    T_Token b;
    out_tokens.clear();
    for (int32_t token_num = 0; token_num < in_tokens.size(); token_num++){
        T_Token t = in_tokens[token_num];
        switch (t.type){
        case number:
        case identificator:
            out_tokens.push_back(t);
            break;
        case binary_operator:
            if (loc_stack.empty()){
                loc_stack.push_back(t);
            } else {
                QMap <QChar, uint32_t>::iterator loc_priority = priority_operator_set.find((QChar)t.str[0]);
                b = loc_stack.back();
                QMap <QChar, uint32_t>::iterator loc_stack_priority = priority_operator_set.find((QChar)b.str[0]);

                while ((loc_priority.value() <= loc_stack_priority.value())&&(!loc_stack.empty())){
                    loc_stack.pop_back();
                    out_tokens.push_back(b);
                    if (!loc_stack.empty()){
                        b = loc_stack.back();
                        loc_stack_priority = priority_operator_set.find((QChar)b.str[0]);
                    }
                }
                loc_stack.push_back(t);
            }
            break;
        case unary_operator:
            loc_stack.push_back(t);
            break;
        case open_bracket:
            loc_stack.push_back(t);
            break;
        case close_bracket:

            if (!loc_stack.empty()){
                b = loc_stack.back();
                loc_stack.pop_back();
            }
            while ( (b.str[0]!='(') && (!loc_stack.empty()) ){
                out_tokens.push_back(b);
                if (!loc_stack.empty()){
                    b = loc_stack.back();
                    loc_stack.pop_back();
                }
            }
            break;
        default:
            break;
        }
    }
    while (!loc_stack.empty()){
        T_Token b = loc_stack.back();
        loc_stack.pop_back();
        out_tokens.push_back(b);
    }
    return loc_err;
}

//------------------------------------------------------------------------------------------------
// Вычисление математического выражения в обратной польской нотации
//------------------------------------------------------------------------------------------------
double T_Math_Expression::RPN_Evaluate(const QVector <T_Token> &in_tokens,
                                       QString &p_err_str,
                                       QString &p_units){
    bool ok=0;
    QMap <QString, TUnitsConverter*> ::iterator it_id = metric_set.end();
    QVector <double> res;
    QVector <SI_Units> resUnits;
    for (int32_t token_num = 0; token_num < in_tokens.size(); token_num++){
        T_Token t = in_tokens[token_num];
        switch (t.type){
        case number:
            res.push_back((t.str).toDouble(&ok));
            if (ok){
                SI_Units units;
                resUnits.push_back(units);            }
            else{
                p_err_str = "Error expression (" + t.str + ")";
                return 0;
            }
            break;
        case identificator:
            it_id = metric_set.find(t.str);
            if (it_id != metric_set.end()){
                res.push_back(it_id.value()->coef);
                SI_Units units;
                units.unit[it_id.value()->baseUnitInd] = 1;
                resUnits.push_back(units);
            }else{
                p_err_str = "Error expression (" + t.str + ")";
                return 0;
            }
            break;
        case binary_operator:
            {
                double o1, o2;
                SI_Units ou1, ou2;
                if (!res.empty()){

                    o2 = res.back();
                    res.pop_back();
                    ou2 = resUnits.back();
                    resUnits.pop_back();
                }else{
                    p_err_str = "Error expression (" + t.str + ")";
                    return 0;
                }
                if (!res.empty()){
                    o1 = res.back();
                    res.pop_back();
                    ou1 = resUnits.back();
                    resUnits.pop_back();
                }else{
                    p_err_str = "Error expression (" + t.str + ")";
                    return 0;
                }
                if (t.str == "+"){
                    res.push_back(o1+o2);
                    if (ou1 != ou2){
                        p_err_str = "Error expression (" + t.str + ")";
                        return 0;
                    } else{
                        resUnits.push_back(ou1);
                    }
                }
                if (t.str == "-"){
                    res.push_back(o1-o2);
                    if (ou1 != ou2){
                        p_err_str = "Error expression (" + t.str + ")";
                        return 0;
                    } else{
                        resUnits.push_back(ou1);
                    }
                }
                if (t.str == "*"){
                    res.push_back(o1*o2);
                    resUnits.push_back(ou1*ou2);
                }
                if (t.str == "/"){
                    res.push_back(o1/o2);
                    resUnits.push_back(ou1/ou2);
                }
                if (t.str == "^"){
                    res.push_back(pow(o1,o2));
                    SI_Units unit;
                    if (ou2 != unit){
                        p_err_str = "Error expression (" + t.str + ")";
                        return 0;
                    }
                    resUnits.push_back(pow(ou1,o2));
                }
            }
            break;
        case unary_operator:
            double o;
            if (!res.empty()){
                o = res.back();
                res.pop_back();
            }else{
                p_err_str = "Error expression (" + t.str + ")";
                return 0;
            }
            if (t.str == "+"){
                res.push_back(o);
            }
            if (t.str == "-"){
                res.push_back(-o);
            }
            break;
        case start:
        case open_bracket:
        case close_bracket:
        case end:
            break;
        }
    }

    if (res.empty()){
        return 0;
    } else{
        p_units = resUnits.back().toString();
        return res.back();
    }
}


//------------------------------------------------------------------------------------------------
// Функция удаления пробелов в строке
//------------------------------------------------------------------------------------------------
QString T_Math_Expression::despacing(const QString &p_str){
    QString out_str="";
    for (int32_t i = 0; i < p_str.size(); i++){
        QChar c = p_str[i];
        if (c != ' ')
            out_str.push_back(c);
    }
    return out_str;
}

//------------------------------------------------------------------------------------------------
// Функция деление строки (математического выражения) на слова (лексемы) следующих типов:
//          - числа (целые или дробные);
//          - бинарные односимвольные операции ( +, -, *, /, ^);
//          - унарные односимвольные операции ( +, -);
//          - скобки '(' и ')';
//          - идентификатры (NM, FL, ft, hour, km, grad, sec, m, min, rad , ...).
//
// Допустимый порядок следования лексем:
//      в начале строки:
//                      - число;
//                      - символьная константа;
//                      - унарный оператор;
//                      - открывающая скобка;
//      после числа или символьной константы:
//                      - бинарный оператор;
//                      - закрывающая скобка;
//      после бинарного оператора:
//                      - число;
//                      - символьная константа;
//                      - открывающая скобка;
//      после унарного оператора:
//                      - число;
//                      - символьная константа;
//                      - отктрывающая скобка;
//      после открывающей скобки:
//                      - число;
//                      - символьная константа;
//                      - отктрывающая скобка;
//      после закрывающей скобки:
//                      - бинарный оператор;
//                      - закрывающая скобка;
//      в конце строки  -
//
// Выражение записано некорректно если,
//      - имеет непарное количество скобок;
//      - начинается со знака бинарной операции;
//      - Бинарные операторы не имеют двух операндов;
//      - включена неизвестная константа (переменная);
//      - число имеет некорректную форму записи.
//
// необходимо считать колличество открывающих и закрывающих скобок
//------------------------------------------------------------------------------------------------
uint32_t T_Math_Expression::string_to_tokens(const QString &p_str,
                                             QVector <T_Token> &p_tokens,
                                             QString &p_err_str){
    uint32_t loc_err=0;
    T_Token loc_token;
    int32_t loc_brackets_count = 0;
    QString::const_iterator loc_it_str = p_str.begin();
    p_tokens.clear();
    loc_token.type = start;

    //p_str = despacing (p_str);

    while (loc_it_str != p_str.end()){
        QChar c = *loc_it_str;
        switch (loc_token.type)
        {

        case start:
            // в начале строки:
            //                  - число;
            //                  - символьная константа;
            //                  - унарный оператор;
            //                  - открывающая скобка;
            //                  - конец строки;
            if (c == ' ')
                break;
            if (c.isDigit()){      // число
                loc_token.type = number;
                loc_token.str.push_back(c);
                break;
            }
            if (abc.contains(c)){  // символьная константа;
                loc_token.type = identificator;
                loc_token.str.push_back(c);
                break;
            }
            if (unary_operator_set.contains(c)){  // унарный оператор;
                loc_token.type = unary_operator;
                loc_token.str.push_back(c);
                break;
            }
            if (c == '('){  // открывающая скобка;
                loc_brackets_count++;
                loc_token.type = open_bracket;
                loc_token.str.push_back(c);
                break;
            }
            p_err_str = "invalid character in the beginning of the line";
            return loc_err = 1;
        case number:
            // после числа:
            //                  - бинарный оператор;
            //                  - закрывающая скобка;
            //                  - конец строки;

            if (c.isDigit() || (c=='.')){      // число (целое или дробное)
                loc_token.str.push_back(c);
                break;
            }
            if (c == ' ')
                break;
            if (binary_operator_set.contains(c)){  // бинарный оператор;
                p_tokens.push_back(loc_token);
                loc_token.type = binary_operator;
                loc_token.str = c;
                break;
            }
            if (c ==')'){  // закрывающая скобка;
                loc_brackets_count--;
                if (loc_brackets_count<0){
                    p_err_str = "Missing opening brackets";
                    return loc_err=1;
                }
                p_tokens.push_back(loc_token);
                loc_token.type = close_bracket;
                loc_token.str = c;
                break;
            }
            p_err_str = "Wrong number format or missing operator";
            return loc_err = 1;
        case identificator:
            //      после символьной константы:
            //                      - бинарный оператор;
            //                      - закрывающая скобка;
            //                      - конец строки;

            if (abc.contains(c) || c.isDigit()){      // символьная константа
                loc_token.str.push_back(c);
                break;
            }
            if (c == ' ')
                break;
            if (binary_operator_set.contains(c)){  // бинарный оператор;
                p_tokens.push_back(loc_token);
                loc_token.type = binary_operator;
                loc_token.str = c;
                break;
            }
            if (c == ')'){  // закрывающая скобка;
                loc_brackets_count--;
                if (loc_brackets_count<0){
                    p_err_str = "Missing opening brackets";
                    return loc_err=1;
                }
                p_tokens.push_back(loc_token);
                loc_token.type = close_bracket;
                loc_token.str = c;
                break;
            }
            p_err_str = "Wrong identifier format or missing operator";
            return loc_err = 1;
        case binary_operator:
            //      после бинарного оператора:
            //                      - число;
            //                      - символьная константа;
            //                      - открывающая скобка;

            if (c == ' ')
                break;

            if (c.isDigit()){      // число
                p_tokens.push_back(loc_token);
                loc_token.type = number;
                loc_token.str = c;
                break;
            }
            if (abc.contains(c)){  // символьная константа;
                p_tokens.push_back(loc_token);
                loc_token.type = identificator;
                loc_token.str = c;
                break;
            }
            if (c == '('){  // открывающая скобка;
                loc_brackets_count++;
                p_tokens.push_back(loc_token);
                loc_token.type = open_bracket;
                loc_token.str = c;
                break;
            }
            if (unary_operator_set.contains(c)){  // унарный оператор;
                p_tokens.push_back(loc_token);
                loc_token.type = unary_operator;
                loc_token.str = c;
                break;
            }
            p_err_str = "The second operand is not available";
            return loc_err = 1;
        case unary_operator:
            //      после унарного оператора:
            //                      - число;
            //                      - символьная константа;
            //                      - отктрывающая скобка;

            if (c == ' ')
                break;

            if (c.isDigit()){      // число
                p_tokens.push_back(loc_token);
                loc_token.type = number;
                loc_token.str = c;
                break;
            }
            if (abc.contains(c)){  // символьная константа;
                p_tokens.push_back(loc_token);
                loc_token.type = identificator;
                loc_token.str = c;
                break;
            }
            if (c=='('){  // открывающая скобка;
                loc_brackets_count++;
                p_tokens.push_back(loc_token);
                loc_token.type = open_bracket;
                loc_token.str = c;
                break;
            }
            if (unary_operator_set.contains(c)){  // унарный оператор;
                p_tokens.push_back(loc_token);
                loc_token.type = unary_operator;
                loc_token.str = c;
                break;
            }
            p_err_str = "The operand is not available";
            return loc_err = 1;
        case open_bracket:
            //      после открывающей скобки:
            //                      - число;
            //                      - символьная константа;
            //                      - отктрывающая скобка;

            if (c==' ')
                break;

            if (c.isDigit()){      // число
                p_tokens.push_back(loc_token);
                loc_token.type = number;
                loc_token.str = c;
                break;
            }
            if (abc.contains(c)){  // символьная константа;
                p_tokens.push_back(loc_token);
                loc_token.type = identificator;
                loc_token.str = c;
                break;
            }
            if (c=='('){  // открывающая скобка;
                loc_brackets_count++;
                p_tokens.push_back(loc_token);
                loc_token.type = open_bracket;
                loc_token.str = c;
                break;
            }
            if (unary_operator_set.contains(c)){  // унарный оператор;
                p_tokens.push_back(loc_token);
                loc_token.type = unary_operator;
                loc_token.str = c;
                break;
            }
            p_err_str = "Incorrect expression after opening brackets";
            return loc_err = 1;
        case close_bracket:
            //      после закрывающей скобки:
            //                      - бинарный оператор;
            //                      - закрывающая скобка;
            //                      - конец строки.

            if (c==' ')
                break;

            if (binary_operator_set.contains(c)){  // бинарный оператор;
                p_tokens.push_back(loc_token);
                loc_token.type = binary_operator;
                loc_token.str = c;
                break;
            }
            if (c==')'){  // закрывающая скобка;
                loc_brackets_count--;
                if (loc_brackets_count<0){
                    p_err_str = "Missing opening brackets";
                    return loc_err=1;
                }
                p_tokens.push_back(loc_token);
                loc_token.type = close_bracket;
                loc_token.str = c;
                break;
            }
            p_err_str = "Incorrect expression after closing brackets";
            return loc_err = 1;
        default:
            p_err_str = "Internal parser error"; // для надежности кода
            return loc_err = 1;
        }
        loc_it_str++;
    }
    if (loc_token.type != start){
        p_tokens.push_back(loc_token);
        if (loc_brackets_count!=0){
            if (loc_brackets_count>0)
                p_err_str = "Missing closing brackets";
            if (loc_brackets_count<0)
                p_err_str = "Internal parser error"; // для надежности кода
            loc_err = 1;
        }
        if ((loc_token.type == unary_operator) || (loc_token.type == binary_operator)){
            p_err_str = "Expression ends with the operator";
            loc_err = 1;
        }
    }
    return loc_err;
}
