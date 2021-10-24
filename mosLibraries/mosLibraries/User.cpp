#include <ctime>
#include <cstdlib>
#include "Constants.h"
#include "structs.h"

extern std::vector<BookDetail> Library;

std::map<int, BookDetail> User::getRecommendations(const int numbRecommends)
{
    std::map<int, BookDetail> result;
    //for (int it = 0; it < numbRecommends; it++) {
    //    int maxSZ = this->recommendations.size();
    //    srand(time(0));
    //    int pos_chosenBook = (long)(std::rand() / RAND_MAX * maxSZ);
    //    
    //    std::map<int, BookDetail>::iterator iter_chosenBook = this->recommendations.find(pos_chosenBook);
    //    while ( result.find(pos_chosenBook) != result.end()) {
    //        srand(time(0));
    //        pos_chosenBook = (std::rand() / RAND_MAX * maxSZ);
    //        iter_chosenBook = this->recommendations.find(pos_chosenBook);
    //    }
    //    result.insert(*iter_chosenBook);
    //}
    std::map<int, BookDetail>::reverse_iterator iter_chosenBook = this->recommendations.rbegin();
    for (int it = 0; it < numbRecommends && iter_chosenBook != this->recommendations.rend(); it++, iter_chosenBook++) {
        if (iter_chosenBook == this->recommendations.rend()) {
            break;
        }
        result.insert(*iter_chosenBook);
    }

    return result;
}

void User::changeRecommendations() {
    this->recommendations.clear();
    //хранение скорее всего не является оптимизированным, т.к. лишние проходы по циклам
    std::map<Date, BookDetail>::iterator it_hist = this->history.begin();
    std::multimap<int, std::pair<double, BookDetail> > recommendationsBYrubrics;
    std::multimap<int, std::pair<double, BookDetail> > recommendationsBYauthor;
    std::multimap<int, std::pair<double, BookDetail> > recommendationsBYpublisher;
    std::multimap<int, std::pair<double, BookDetail> > recommendationsBYpages;
    std::multimap<std::string, std::pair<double, BookDetail> > recommendationsBYkeyword;


    // Из истории
    for (; it_hist != this->history.end(); it_hist++) {
        int rubric_hist = it_hist->second.rubric_id;
        int author_hist = it_hist->second.author_id;
        int publisher_hist = it_hist->second.publisher_id;
        int pages_hist = it_hist->second.pages;
        std::string keyword_hist = it_hist->second.keyword;

        //По рубрике
        std::multimap<int, std::pair<double, BookDetail> >::iterator it_recommend = recommendationsBYrubrics.begin();
        unsigned int cnt_cur_rubrics = 0;
        for (; it_recommend != recommendationsBYrubrics.end(); it_recommend++) {
            if (it_recommend->first == rubric_hist) {
                it_recommend->second.first += WEIGHT_RUBRIC;
                cnt_cur_rubrics++;
            }
        }
        if (!cnt_cur_rubrics) {
            for (int it = 0; it < Library.size(); it++) {
                if (Library.at(it).rubric_id == rubric_hist) {
                    recommendationsBYrubrics.insert(std::make_pair(rubric_hist, std::make_pair(WEIGHT_RUBRIC, Library.at(it))));
                    cnt_cur_rubrics++;
                }
            }
        }
        //std::multimap<int, std::pair<double, BookDetail> >::iterator 
            it_recommend = recommendationsBYrubrics.begin();
        for (; it_recommend != recommendationsBYrubrics.end(); it_recommend++) {
            recommendationsBYauthor.insert(std::make_pair(it_recommend->second.second.author_id, std::make_pair(it_recommend->second.first, it_recommend->second.second)));
        }
        recommendationsBYrubrics.clear();

        //ПО автору
        //std::multimap<int, std::pair<double, BookDetail> >::iterator 
            it_recommend = recommendationsBYauthor.begin();
        unsigned int cnt_cur_author = 0;
        for (; it_recommend != recommendationsBYauthor.end(); it_recommend++) {
            if (it_recommend->first == author_hist) {
                it_recommend->second.first += WEIGHT_AUTHOR;
                cnt_cur_author++;
            }
        }
        if (!cnt_cur_author) {
            for (int it = 0; it < Library.size(); it++) {
                if (Library.at(it).rubric_id == author_hist) {
                    recommendationsBYauthor.insert(std::make_pair(author_hist, std::make_pair(WEIGHT_AUTHOR, Library.at(it))));
                    cnt_cur_author++;
                }
            }
        }
        //std::multimap<int, std::pair<double, BookDetail> >::iterator 
            it_recommend = recommendationsBYauthor.begin();
        for (; it_recommend != recommendationsBYauthor.end(); it_recommend++) {
            recommendationsBYpublisher.insert(std::make_pair(it_recommend->second.second.publisher_id, std::make_pair(it_recommend->second.first, it_recommend->second.second)));
        }
        recommendationsBYauthor.clear();

        //По издателю
        //std::multimap<int, std::pair<double, BookDetail> >::iterator 
            it_recommend = recommendationsBYpublisher.begin();
        unsigned int cnt_cur_publisher = 0;
        for (; it_recommend != recommendationsBYpublisher.end(); it_recommend++) {
            if (it_recommend->first == publisher_hist) {
                it_recommend->second.first += WEIGHT_PUBLISHER;
                cnt_cur_publisher++;
            }
        }
        if (!cnt_cur_publisher) {
            for (int it = 0; it < Library.size(); it++) {
                if (Library.at(it).rubric_id == publisher_hist) {
                    recommendationsBYpublisher.insert(std::make_pair(publisher_hist, std::make_pair(WEIGHT_PUBLISHER, Library.at(it))));
                    cnt_cur_publisher++;
                }
            }
        }
        //std::multimap<int, std::pair<double, BookDetail> >::iterator 
            it_recommend = recommendationsBYpublisher.begin();
        for (; it_recommend != recommendationsBYpublisher.end(); it_recommend++) {
            recommendationsBYpages.insert(std::make_pair(it_recommend->second.second.pages, std::make_pair(it_recommend->second.first, it_recommend->second.second)));
        }
        recommendationsBYpublisher.clear();

        //По количеству страниц
        //std::multimap<int, std::pair<double, BookDetail> >::iterator 
        it_recommend = recommendationsBYpages.begin();
        unsigned int cnt_cur_pages = 0;
        for (; it_recommend != recommendationsBYpages.end(); it_recommend++) {
            if (std::abs(it_recommend->first - pages_hist) <= diffPages4weight) {
                it_recommend->second.first += WEIGHT_PAGES;
                cnt_cur_pages++;
            }
        }
        ////std::multimap<int, std::pair<double, BookDetail> >::iterator 
        //it_recommend = recommendationsBYpages.begin();
        //for (; it_recommend != recommendationsBYpages.end(); it_recommend++) {
        //    recommendationsBYkeyword.insert(std::make_pair(it_recommend->second.second.keyword, std::make_pair(it_recommend->second.first, it_recommend->second.second)));
        //}
        //recommendationsBYpages.clear();

        ////По ключевым словам, в т.ч. из аннотации/названия
        //std::multimap<std::string, std::pair<double, BookDetail> >::iterator 
        //    it_recommend_str = recommendationsBYkeyword.begin();
        //unsigned int cnt_cur_keyword = 0;
        //for (; it_recommend_str != recommendationsBYkeyword.end(); it_recommend_str++) {
        //    if ( keyword_hist.find(it_recommend_str->first) >= 0) {
        //        it_recommend_str->second.first += WEIGHT_KEYWORD;
        //        cnt_cur_keyword++;
        //    }
        //}


    }
    std::multimap<int, std::pair<double, BookDetail> >::iterator 
    it_recommend = recommendationsBYpages.begin();
    for (; it_recommend != recommendationsBYpages.end(); it_recommend++) {
        this->recommendations.insert(std::make_pair(it_recommend->second.first, it_recommend->second.second));
    }
    recommendationsBYpages.clear();

}

void User::setRecommendations() {
    time_t cur_time = time(0);
    struct tm *timeUpdate = localtime(&cur_time);
    timeUpdate->tm_hour = 3;
    timeUpdate->tm_min = 0;
    timeUpdate->tm_sec = 0;
    if (time(0) == mktime(timeUpdate)) {
        this->changeRecommendations();
    }
}