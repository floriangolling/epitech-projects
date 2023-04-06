//
// Created by jbroesch on 11/04/2021.
//

#include "SaveHighScore.hpp"

namespace Arcade {
    bool sortbysecdesc(std::vector<std::string> a, std::vector<std::string> b) {
        return (atoi(a[2].c_str()) < atoi(b[2].c_str()));
    }

    std::vector<std::vector<std::string>> parse_file() {
        std::vector<std::vector<std::string>> result;
        std::ifstream file("./GamesLib/Highscore/highscore.txt");
        std::string line;
        if (!file) {
            std::cerr << "Highscore file cannot be opened!" << std::endl;
            throw std::exception();
        }
        while (std::getline(file, line)) {
            int i = 0;
            std::vector<std::string> result_split;
            std::istringstream ss(line);
            std::string word;
            while (ss >> word && i < 3) {
                result_split.push_back(word);
                i++;
            }
            if (i != 3)
                continue;
            if (atoi(result_split[2].c_str()) != 0)
                result.push_back(result_split);
        }
        sort(result.rbegin(), result.rend(), sortbysecdesc);
        return (result);
    }

    void save_score(std::string username, int score, std::string gameName) {
        if (score == 0)
            return;
        std::vector<std::vector<std::string>> lines = parse_file();
        std::vector<std::string> newLine;
        newLine.push_back(gameName);
        newLine.push_back(username);
        newLine.push_back(std::to_string(score));
        lines.push_back(newLine);
        sort(lines.rbegin(), lines.rend(), sortbysecdesc);

        std::ofstream ofs;
        ofs.exceptions(std::ifstream::badbit);

        try {
            ofs.open("./GamesLib/Highscore/highscore.txt", std::ofstream::trunc);
            int i = 0;
            for (auto it = lines.begin(); it != lines.end(); it++, i++) {
                if (i == 10)
                    break;
                ofs << (*it)[0] << " " << (*it)[1] << " " << (*it)[2] << std::endl;
            }
        }
        catch (std::ofstream::failure &e) {
            std::cerr << "Can't open/read/close file : highscore.txt" << std::endl;
            throw std::exception();
        }
        ofs.close();
        return;
    }
}