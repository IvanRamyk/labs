//
// Created by Ivan Ramyk on 10/28/19.
//

#ifndef TASK2_FUNCTION_HXX
#define TASK2_FUNCTION_HXX


template<>
std::string Function::calculate(int x) {
    Translate<int> translate;
    if (x > 0)
        return translate.translate((x * x) % 110);
    int res = x * x * x * x * x + x * x * x;
    res = ((res % 210) + 210) % 210;
    return translate.translate(res);
}

template<>
std::string Function::calculate(double x) {
    Translate<double> translate;
    return translate.translate(sin(x + 510));
}

template<>
std::string Function::calculate(std::string x) {
    std::stringstream ss(x);
    std::vector<std::string> words;
    std::string word;
    while (ss >> word)
        words.push_back(word);
    std::reverse(words.begin(), words.end());
    word = "";
    for (auto i : words) {
        word += i;
        word += " ";
    }
    word.erase(--(word.end()));
    return word;
}

template<typename FirstArgumentT, typename SecondArgumentT>
std::string Function::calculate(std::pair<FirstArgumentT, SecondArgumentT> x) {
    return calculate(x.second) + " " + calculate(x.first);
}

template<typename ArgumentT>
std::string Function::calculate(std::vector<ArgumentT> x) {
    std::set<std::string> s;
    for (auto i : x)
        s.insert(calculate(i));
    std::string answer = "";
    for (auto i : s) {
        answer += i;
        answer += " ";
    }
    answer.erase((--answer.end()));
    return answer;
}

template<typename ArgumentT>
std::string Function::calculate(ArgumentT x) {
    return "sorry please try again";
}

#endif //TASK2_FUNCTION_HXX
