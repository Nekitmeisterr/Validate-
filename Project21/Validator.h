#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
class Validator
{public :

    bool validate(const std::string& data)
    {
        // ќни должны быть одинакового размера, если html действителен.
        // Ќа основе совпадени€ тегов
        std::unordered_set<std::string> opening_tags, closing_tags;

        // ѕодобных тегов '<br />'
        std::unordered_set<std::string> self_closing_tags;

        //ќтслеживает текущий тег, чтобы вставить его в любой
        // открывающие теги или закрывающие теги
        bool tagging_open;

        // ќбрабатывает  каждый символ, чтобы сделать теги
        for (size_t i = 0; i < data.size(); ++i)
        {
            const auto* cur_char = &data.at(i);

            if (*cur_char == '<')
            {
                std::string cur_tag;

                if (*(cur_char + 1) == '/')
                { // “ест на закрывающий тег
                    tagging_open = false;
                    i++;
                    cur_char++;
                }
                else // “ег €вл€етс€ открывающим тегом
                    tagging_open = true;

                i++;
                cur_char++;
                while (*cur_char != '>') // ѕока тег не закроетс€
                {
                    cur_tag += *cur_char;
                    i++;
                    cur_char++;
                }

                // “ест на самозакрывающийс€ тег
                if (*(cur_char - 1) == '/')
                    self_closing_tags.insert(cur_tag);
                // ¬ случае если это обычный тег
                else if (tagging_open)
                    opening_tags.insert(cur_tag);
                else if (!tagging_open)
                    closing_tags.insert(cur_tag);
            }
        }

        // ≈сли хеш-наборы не одного размера, мы автоматически узнаем
        // есть хот€ бы один несопоставленный тег
        if (opening_tags.size() != closing_tags.size())
            return false;

        // ≈сли оба набора хэшей пусты, то мы знаем, что тегов нет.
        if (opening_tags.empty())
            return false;

        // ≈сли оба вышеупом€нутых теста были пройдены, теперь нам нужно убедитьс€, что
        // каждый открывающий тег имеет соответствующий закрывающий тег
        std::vector<bool> tag_match(opening_tags.size(), false);
        size_t tag_match_pos = 0;
        for (const auto& tag : opening_tags)
        {
            auto closing_tag_itr = closing_tags.find(tag);
            if (closing_tag_itr != std::end(closing_tags))
            {
                tag_match.at(tag_match_pos) = true;
                tag_match_pos++;

                // ”даление тегов совпадени€, чтобы дубликаты не вызывали ложных срабатываний.
                closing_tags.erase(closing_tag_itr);
            }
        }
        bool all_matched = true;
        for (const auto& match : tag_match)
        { // ѕроверка что все значени€ верны
            if (!match)
            {
                all_matched = false;
                break;
            }
        }

        return all_matched;
    }
};



