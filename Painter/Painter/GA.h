#pragma once

#include <vector>
#include "Solution.h"
#include "Image.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAX_CIRCLE_SIZE = 3000;

class GA
{
	Image origin, pic;
    std::vector<Solution> soluSet;
    std::vector<Solution> child;
	Solution bestSol;

    int divide_width=10, divide_height=10;
    int poolSize = 30;
    int select_num = 6;
    int generation = 0;

    void SortSolution()
    {
        for(int i=0; i<soluSet.size(); i+=1) {
			if (soluSet[i].hasScore)
				continue;
			soluSet[i].DrawAllCircle(pic);
			soluSet[i].score = origin.CalcDifference(pic);
			soluSet[i].hasScore = true;
        }
        sort(soluSet.begin(), soluSet.end());
    }

public:
    bool initial(char fileName[])
    {
		origin.Read(fileName);
		if (origin.isEmpty()) return false;
        
		origin.Show("original Picture");
		origin.copyTo(pic);

		bestSol.score = 1e9;
        return true;
    }

    void generateInitSolution()
    {
//        Solution x5050(50, 50, origin);
//        Solution x3030(30, 30, origin);
//
//        x5050.DrawAll(pic);
//        cvpic.show("50 50", pic);
//        cout << pic.CalcDifference(origin) << endl;
//        x3030.DrawAll(pic);
//        cvpic.show("30 30", pic);
//        cout << pic.CalcDifference(origin) << endl;

        for(int p=0; p<poolSize; p+=1) {
            Solution tempS(divide_height, divide_width, origin);
            soluSet.push_back(tempS);
        }
    }

    // 選出 select_num 個 solution 來當成 mating
    void Roulette_Wheel_Seletion();
//    void start2_4()
//    {
//        generateInitSoluction();
//        bool tag = true;
//        int row=2, col=4, r=0, c=0;
//        //cvpic.show("new 30-2", pic);
//        while(generation<100000)
//        {
//
//            Roulette_Wheel_Seletion();
//            for(int i=0;i<child.size();i+=2){
//                child[i].Crossover(child[i+1],divide_height,divide_width);
//                soluSet.push_back(child[i]);
//                soluSet.push_back(child[i+1]);
//            }
//            Sort(soluSet);
//            while(soluSet.size()>parent){
//                soluSet.pop_back();
//            }
//
//            for(int i=0;i<soluSet.size();i++)
//            {   if((rand()%100)>70)
//                    soluSet[i].AddCircle(origin,divide_height,divide_width);
//            }
//
//            soluSet[0].DrawAll(pic);
//
//            stringstream ss;
//            ss << r << "-" << c;
//            string wind;
//            ss >> wind;
//            wind = "Generation " + wind;
//            cvpic.show(wind.c_str(), pic);
//            cvpic.moveWindow(wind.c_str(), 20+origin.width*c, 20+origin.height*r);
//
//            c += 1; c %= col;
//            if( c==0 ) {
//                r += 1; r %= row;
//            }
//
////            if(genZeration%100==0)
//                cvWaitKey();
//
//            generation++;
//            cout << generation << endl;
//        }
//    }

    void Start()
    {
		// 建立 poolsize 個 initial
        generateInitSolution();

        //bool tag = true;
        //int row=2, col=4, r=0, c=0;

		while(true)
        //while(generation<100000)
        {
            cout << generation << endl;

			// create child solutions 
			std::cout << "start wheel selection" << std::endl;
            Roulette_Wheel_Seletion();
			std::cout << "end wheel selection" << std::endl;

            for(int i=0;i<child.size();i+=2){
				
				if (child[i].CalCircleNumbers() < MAX_CIRCLE_SIZE && child[i].CalCircleNumbers() < MAX_CIRCLE_SIZE) {
					child[i].Crossover(child[i + 1], divide_height, divide_width);
					soluSet.push_back(child[i]);
					soluSet.back().hasScore = false;
					soluSet.push_back(child[i + 1]);
					soluSet.back().hasScore = false;
				}
            }
			
			/*for (int i = 0; i < soluSet.size(); i += 1) {
				std::cout << "Score[" << i << "]:" << soluSet[i].score << std::endl;
			}*/

			std::cout << "start sort solution" << std::endl;
            SortSolution();
			std::cout << "end sort solution" << std::endl;

            //while(soluSet.size()>poolSize){
            //    soluSet.pop_back();
            //}

			std::cout << "start add circle" << std::endl;
            for(int i=0;i<soluSet.size();i++)
            {
				int circleNum = 1;
				for (int num = 0; num < circleNum; num += 1) {
					if (soluSet[i].CalCircleNumbers() >= MAX_CIRCLE_SIZE)
						break;
					soluSet[i].AddCircle(origin, divide_height, divide_width, soluSet[i].CalCircleNumbers(), pic);
				}  
            }
			std::cout << "end add circle" << std::endl;
			
			//for (int i = 0; i < soluSet.size(); i += 1) {
			//	if (soluSet[i].CalCircleNumbers() >=295)
			//		soluSet[i].DiscardRedant(origin, divide_height, divide_width, pic);
			//}
			
			if (soluSet[0].score < bestSol.score) {
				bestSol = soluSet[0];
				bestSol.DrawAllCircle(pic);
				std::string wind = "image/Best " + std::to_string(generation) + ".jpg";
				cout << wind << endl;
				pic.Write(wind.c_str());
			}

            if(generation%1==0){
				soluSet[0].DrawAllCircle(pic);
				
				std::string wind = "image/Generation " + std::to_string(generation) + ".jpg";
				cout << wind << endl;
				pic.Write(wind.c_str());

				cout << "Generation " << generation << endl;
                cout << "Circles:" << soluSet[0].CalCircleNumbers() << endl;
				cout << "fitness:" << pic.CalcDifference(origin) << std::endl;

				std::cout << "Best solution circle size:" << soluSet[0].CalCircleNumbers() << std::endl << std::endl;
            }

			std::cout << "start mutation" << std::endl;
			for (int i = 0; i<soluSet.size(); i += 1) {
				while (soluSet[i].CalCircleNumbers() > MAX_CIRCLE_SIZE) {
					soluSet[i].Mutation(origin, divide_height, divide_width, pic);
				}

				if(rand()%100 > 60)
					soluSet[i].Mutation(origin, divide_height, divide_width, pic);
			}
			std::cout << "end mutation" << std::endl;

			while(soluSet.size()>poolSize){
			    soluSet.pop_back();
			}

			generation++;
        }
    }

};

