#include "GA.h"
//#include <algorithm>

void GA::Roulette_Wheel_Seletion()
{
	vector<double> scores(soluSet.size());
	for (int i = 0; i < scores.size(); i += 1) {
		soluSet[i].DrawAllCircle(pic);
		scores[i] = origin.CalcDifference(pic) + 1;
	}
	double max_val = *max_element(scores.begin(), scores.end());
	//double min_val = *min_element(scores.begin(), scores.end());

    vector<double> CDF(soluSet.size());
	soluSet[0].DrawAllCircle(pic);
	CDF[0] = (max_val - scores[0]);

    for(int i=1; i<CDF.size(); i+=1) {
		CDF[i] = CDF[i - 1] + max_val - scores[i];
    }

    child.clear();
    // select_num 是要選出的個數
    for(int i=0; i<select_num; i+=1) {
		/*if (CDF.back() >= 9223372036854775807.0) {
			std::cout << "=========Over flow=========" << std::endl;
		}*/
        double random = rand()%(long long int)CDF.back();
        int ind = lower_bound(CDF.begin(), CDF.end(), random) - CDF.begin();
		/*if (ind >= soluSet.size()) {
			std::cout << "=========array out of range=========" << std::endl;
			ind -= 1;
		}*/
        child.push_back(soluSet[ind]);
    }
}
