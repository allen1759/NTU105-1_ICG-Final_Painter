#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "Circle.h"
#include "Image.h"

class Solution
{
public:
    std::vector< std::vector< std::vector<Circle> > > sol;
    int score;
	bool hasScore = false;

    Solution() {}

    Solution(int divide_height, int divide_width, Image &origin)
    {
        sol.resize(divide_height);
        for(int i=0; i<divide_height; i+=1)
            sol[i].resize(divide_width);

        int areaWidth = (origin.getw()/divide_width) + 1;
        int areaHeight = (origin.geth()/divide_height) + 1;

		for (int x = 0; x < origin.getw(); x += areaWidth) {
			for (int y = 0; y < origin.geth(); y += areaHeight) {
				// can i speedup??
				
				if (x + areaWidth >= origin.getw())
					continue;
				if (y + areaHeight >= origin.geth())
					continue;
				int width = std::min(areaWidth, origin.getw() - x);
				int height = std::min(areaHeight, origin.geth() - y);

				cv::Mat area = origin.GetSubImage(cv::Rect(x, y, width, height));
				cv::Scalar averColor = cv::mean(area);

				const int colorRange = 25; 
				const int alphaRange = 50;
				Circle tempC;
				tempC.B = averColor[0] - colorRange + rand() % (2 * colorRange);
				tempC.G = averColor[1] - colorRange + rand() % (2 * colorRange);
				tempC.R = averColor[2] - colorRange + rand() % (2 * colorRange);
				tempC.A = 128 - alphaRange + rand() % (2 * alphaRange);

				tempC.radius = height / 4 + rand() % (height / 4);
				tempC.x = x + rand() % width;
				tempC.y = y + rand() % height;

				sol[y/areaHeight][x/areaWidth].push_back(tempC);
			}
		}
		hasScore = false;
    }

    bool operator < (const Solution & rhs) const
    {
        return score < rhs.score;
    }
	
	void DrawAllCircle(Image &pic)
	{
		pic.setTo(cv::Scalar(0, 0, 0));

		for (int i = 0; i < sol.size(); i += 1) {
			for (int j = 0; j < sol[i].size(); j += 1) {
				for (int k = 0; k < sol[i][j].size(); k += 1) {
					pic.DrawCircle(sol[i][j][k]);
				}
			}
		}
	}

    void Crossover(Solution &rs, int divide_height, int divide_width)
    {
		int x_part = rand() % divide_width;
		int y_part = rand() % divide_height;
        swap(sol[y_part][x_part], rs.sol[y_part][x_part]);
    }

    void Mutation(Image &origin, int divide_height, int divide_width, Image& pic)
    {
		int deleteNum = rand() % 10 + 5;

		for (int t = 0; t < deleteNum; t += 1) {
			int i = rand() % divide_height;
			int j = rand() % divide_width;

			if (sol[i][j].size() == 0) continue;

			int ind = rand() % (int)sol[i][j].size();
			sol[i][j].erase(sol[i][j].begin() + ind);
		}
    }

	//void Mutation(Image &origin, int divide_height, int divide_width, Image& pic)
	//{
	//	int num = rand() % (divide_height*divide_width / 2);

	//	DrawAllCircle(pic);
	//	score = origin.CalcDifference(pic);
	//	
	//	for (int k = 0; k<num; k += 1) {
	//		int i = rand() % divide_height;
	//		int j = rand() % divide_width;

	//		for (int t = 0; t<sol[i][j].size(); t += 1) {
	//			Solution tmp = (*this);
	//			tmp.sol[i][j].erase(tmp.sol[i][j].begin() + t);
	//			tmp.DrawAllCircle(pic);
	//			tmp.score = origin.CalcDifference(pic);

	//			if (tmp.score<score) {
	//				sol[i][j].erase(sol[i][j].begin() + t);
	//				break;
	//			}
	//		}
	//	}
	//}

	void DiscardRedant(Image &origin, int divide_height, int divide_width, Image& pic)
	{
		Solution currSol = (*this);

		for (int i = 0; i < divide_height; i += 1) {
			for (int j = 0; j < divide_width; j += 1) {
				std::vector<Circle> best;
				int bestScore = currSol.score;
				for (int k = 0; k < currSol.sol[i][j].size(); k += 1) {
					Solution tmp = currSol;
					
					tmp.sol[i][j].erase(tmp.sol[i][j].begin() + k);
					tmp.DrawAllCircle(pic);
					tmp.score = origin.CalcDifference(pic);

					if (tmp.score < bestScore) {
						best = tmp.sol[i][j];
						bestScore = tmp.score;
					}
				}
				currSol.sol[i][j] = best;
				currSol.score = bestScore;
			}
		}
	}

    void AddCircle(Image &origin, int divide_height, int divide_width, int numOfTotalCircle, Image& pic)
    {
		const int colorRange = 15;
		const int alphaRange = 50;
		Circle tempC;

		int newHeight = origin.geth() / divide_height + 1;
		int newWidth = origin.getw() / divide_width + 1;

		
		tempC.radius = 1 + rand() % (newHeight / 2);
		
		//int tmp = (300 - numOfTotalCircle) * 7 / 100 + 3;
		//tempC.radius = tmp + rand() % (tmp / 3);
		tempC.x = rand() % origin.getw();
		tempC.y = rand() % origin.geth();

		//cv::Vec3f color = origin.GetColor(tempC.x, tempC.y);
		//DrawAllCircle(pic);
		//cv::Vec3f now = pic.GetColor(tempC.x, tempC.y);
		cv::Vec3f color = origin.GetColor(tempC.x, tempC.y, tempC.radius);
		DrawAllCircle(pic);
		cv::Vec3f now = pic.GetColor(tempC.x, tempC.y, tempC.radius);

		tempC.B = color[0] - colorRange + rand() % (2 * colorRange);
		tempC.G = color[1] - colorRange + rand() % (2 * colorRange);
		tempC.R = color[2] - colorRange + rand() % (2 * colorRange);

		//tempC.B = std::max(0.0f, color[0] - now[0]) - colorRange + rand() % (2 * colorRange);
		//tempC.G = std::max(0.0f, color[1] - now[1]) - colorRange + rand() % (2 * colorRange);
		//tempC.R = std::max(0.0f, color[2] - now[2]) - colorRange + rand() % (2 * colorRange);
		tempC.A = 128 - alphaRange + rand() % (2 * alphaRange);

		tempC.B = std::max(0, tempC.B);
		tempC.B = std::min(255, tempC.B);
		tempC.G = std::max(0, tempC.G);
		tempC.G = std::min(255, tempC.G);
		tempC.R = std::max(0, tempC.R);
		tempC.R = std::min(255, tempC.R);

		auto & vec = sol[tempC.y / newHeight][tempC.x / newWidth];
		vec.push_back(tempC);
		if (vec.size() > 10) {
			vec.erase(vec.begin());
		}

		hasScore = false;
    }


    int CalCircleNumbers()
    {
		int num = 0;
		for (int i = 0; i < sol.size(); i += 1) {
			for (int j = 0; j < sol[i].size(); j += 1) {
				num += ((int)sol[i][j].size());
            }
        }
        return num;
    }
};

