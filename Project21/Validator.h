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
        // ��� ������ ���� ����������� �������, ���� html ������������.
        // �� ������ ���������� �����
        std::unordered_set<std::string> opening_tags, closing_tags;

        // �������� ����� '<br />'
        std::unordered_set<std::string> self_closing_tags;

        //����������� ������� ���, ����� �������� ��� � �����
        // ����������� ���� ��� ����������� ����
        bool tagging_open;

        // ������������  ������ ������, ����� ������� ����
        for (size_t i = 0; i < data.size(); ++i)
        {
            const auto* cur_char = &data.at(i);

            if (*cur_char == '<')
            {
                std::string cur_tag;

                if (*(cur_char + 1) == '/')
                { // ���� �� ����������� ���
                    tagging_open = false;
                    i++;
                    cur_char++;
                }
                else // ��� �������� ����������� �����
                    tagging_open = true;

                i++;
                cur_char++;
                while (*cur_char != '>') // ���� ��� �� ���������
                {
                    cur_tag += *cur_char;
                    i++;
                    cur_char++;
                }

                // ���� �� ����������������� ���
                if (*(cur_char - 1) == '/')
                    self_closing_tags.insert(cur_tag);
                // � ������ ���� ��� ������� ���
                else if (tagging_open)
                    opening_tags.insert(cur_tag);
                else if (!tagging_open)
                    closing_tags.insert(cur_tag);
            }
        }

        // ���� ���-������ �� ������ �������, �� ������������� ������
        // ���� ���� �� ���� ���������������� ���
        if (opening_tags.size() != closing_tags.size())
            return false;

        // ���� ��� ������ ����� �����, �� �� �����, ��� ����� ���.
        if (opening_tags.empty())
            return false;

        // ���� ��� �������������� ����� ���� ��������, ������ ��� ����� ���������, ���
        // ������ ����������� ��� ����� ��������������� ����������� ���
        std::vector<bool> tag_match(opening_tags.size(), false);
        size_t tag_match_pos = 0;
        for (const auto& tag : opening_tags)
        {
            auto closing_tag_itr = closing_tags.find(tag);
            if (closing_tag_itr != std::end(closing_tags))
            {
                tag_match.at(tag_match_pos) = true;
                tag_match_pos++;

                // �������� ����� ����������, ����� ��������� �� �������� ������ ������������.
                closing_tags.erase(closing_tag_itr);
            }
        }
        bool all_matched = true;
        for (const auto& match : tag_match)
        { // �������� ��� ��� �������� �����
            if (!match)
            {
                all_matched = false;
                break;
            }
        }

        return all_matched;
    }
};



