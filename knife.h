//
// Created by eggytronixx on 11/19/15.
//

#ifndef KNIFE_H
#define KNIFE_H

#include <vector>
#include <algorithm>
#include <regex>


namespace knife {

    using namespace std;

    namespace _ {


        void forEach(auto &&collection, auto &&f) {

            int i =1;
            for_each(collection.begin(), collection.end(), [&](auto &item) {
                f(item);
            });

        };

        void forEachR(auto &&collection, auto &&f) {
            for_each(collection.rbegin(), collection.rend(), [&](auto &item) {
                f(item);
            });
        };


        auto range(int min, int max = 0) {

            vector<int> numberRange;

            if (max == 0) {
                max = min;
                min = 0;
            }

            for (auto i = min; i <= max; i++) {
                numberRange.push_back(i);
            }

            return numberRange;
        };

        void repeat(auto n, auto &&f) {
            for (auto i = 0; i < n; i++) {
                f(i);
            }
        };

        bool every(auto &&collection, auto &&f) {

            for(auto & item : collection){

                if(!f(item)) return false;
            }

            return true;
        };

        bool contains(auto &&collection, auto &&value) {

            for(auto & item : collection){

                if(value == item) return true;
            }

            return false;
        };


        template<typename T, typename U, typename TF>
        auto reduce(T &&collection, U &&memo, TF &&f) {
            forEach(collection, [&memo, &f](const auto &current) {
                memo = f(memo, current);
            });

            return memo;
        };

        template<typename T, typename U, typename TF>
        auto reduceRight(T &&collection, U &&memo, TF &&f) {

            forEachR(collection, [&](const auto &current) {

                memo = f(memo, current);

            });

            return memo;
        };

        template<typename TF, typename... Ts>
        void forArgs(TF &&f, Ts &&... paramArgs) {

            return (void) initializer_list<int>{
                    (f(forward<Ts>(paramArgs)), 0)...
            };

        }

        template<typename T>
        T without(auto &&collection, const auto &array) {

            T store;
            forEach(collection, [&](const auto &current) {

                bool notFound = true;
                for (auto &&item : array) {

                    if (item == current) {
                        notFound = false;
                    }
                }
                if (notFound) store.insert(store.end(), current);

            });

            return store;
        }

        template<typename T>
        T filter(auto &&collection, auto &&f) {

            T store;

            forEach(collection, [&](const auto &current) {

                if (!f(current)) store.insert(store.end(), current);
            });

            return store;
        }

        template<typename T>
        T reject(auto &&collection, auto &&f) {

            T store;

            forEach(collection, [&](const auto &current) {

                if (f(current)) store.insert(store.end(), current);
            });

            return store;
        }

        template<typename T>
        T map(auto &&collection, auto &&f) {

            T store;

            forEach(collection, [&](const auto &current) {
                store.insert(store.end(), f(current));
            });

            return store;
        }

        template<typename T>
        T find(auto &&collection, auto &&f) {

            for (const auto &item:collection) {
                if (f(item)) return item;
            }

            return T();
        }

        template<typename T>
        T sortBy(auto &&collection, auto &&f) {
            T copy(collection);
            sort(copy.begin(), copy.end(), f);
            return copy;
        }



        // string manipulation 
        vector<string> split(const string & str, auto && exp){

            regex wordsRegex(exp);
            auto wordsBegin = sregex_iterator(str.begin(), str.end(), wordsRegex);
            auto wordsEnd = sregex_iterator();
            vector<string> tokens;

            for (sregex_iterator i = wordsBegin; i != wordsEnd; i++) {
                smatch match = *i;                                                 
                string matchStr = match.str();   
                tokens.push_back(matchStr);
            }

            return tokens; 
        }

        // string replace(string str, string && from, string && to){
            
        //     size_t pos = 0;
        //     while(pos = str.find(from, pos) != string::npos){
        //         cout << str << endl;
        //         str.replace(pos, from.length(), to);
        //         pos += to.length();
        //     }
        //     return str;
        // }

    }
}

#endif