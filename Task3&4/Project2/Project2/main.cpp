#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
using namespace std;
struct artist
{
	double id;
	double danceability;
	double energy;
	double valence;
	double tempo;
	double loudness;
	double mode;
	double key;
	double acousticness;
	double instrumentalness;
	double liveness;
	double speechiness;
	double duration;
	double popularity;
	int label;
	bool operator==(const artist&a)
	{
		return id == a.id;
	}
};
vector<artist>vec;
//double pearson(artist& A, artist& B)
//{
//	double sum_AB = A.instrumentalness*B.instrumentalness+A.acousticness*B.acousticness + A.danceability * B.danceability + A.duration*B.duration + A.energy*B.energy + A.key*B.key + A.liveness*B.liveness + A.loudness*B.loudness + A.mode*B.mode + A.popularity*B.popularity + A.speechiness*B.speechiness + A.tempo*B.tempo + A.valence*B.valence;
//	double sum_A =A.instrumentalness+ A.acousticness + A.danceability + A.duration + A.energy + A.key + A.liveness + A.loudness + A.mode + A.popularity + A.speechiness + A.tempo + A.valence;
//	double sum_B =B.instrumentalness+ B.acousticness + B.danceability + B.duration + B.energy + B.key + B.liveness + B.loudness + B.mode + B.popularity + B.speechiness + B.tempo + B.valence;
//	double sum_A2 = A.instrumentalness*A.instrumentalness+A.acousticness*A.acousticness + A.danceability* A.danceability + A.duration*A.duration + A.energy*A.energy + A.key*A.key + A.liveness*A.liveness + A.loudness* A.loudness + A.mode*A.mode + A.popularity*A.popularity + A.speechiness*A.speechiness + A.tempo* A.tempo + A.valence*A.valence;
//	double sum_B2 =B.instrumentalness*B.instrumentalness+ B.acousticness*B.acousticness + B.danceability* B.danceability + B.duration*B.duration + B.energy*B.energy + B.key*B.key + B.liveness*B.liveness + B.loudness* B.loudness + B.mode*B.mode + B.popularity*B.popularity + B.speechiness*B.speechiness + B.tempo* B.tempo + B.valence*B.valence;
//	int N = 12;
//	double M1 = sum_AB - sum_A * sum_B / (double)N;
//	double M2 = sum_A2 - sum_A * sum_A / (double)N;
//	double M3 = sum_B2 - sum_B * sum_B / (double)N;
//	return M1 / sqrt(M2*M3);
//}
double pearson(artist& A, artist& B)
{
	double sum_AB = A.instrumentalness*B.instrumentalness + A.acousticness*B.acousticness + A.danceability * B.danceability + A.energy*B.energy+ A.speechiness*B.speechiness ;
	double sum_A = A.instrumentalness + A.acousticness + A.danceability  + A.energy + A.speechiness;
	double sum_B = B.instrumentalness + B.acousticness + B.danceability+ B.energy + B.speechiness ;
	double sum_A2 = A.instrumentalness*A.instrumentalness + A.acousticness*A.acousticness + A.danceability* A.danceability + A.energy*A.energy + A.speechiness*A.speechiness;
	double sum_B2 = B.instrumentalness*B.instrumentalness + B.acousticness*B.acousticness + B.danceability* B.danceability + B.energy*B.energy + B.speechiness*B.speechiness ;
	int N = 5;
	double M1 = sum_AB - sum_A * sum_B / (double)N;
	double M2 = sum_A2 - sum_A * sum_A / (double)N;
	double M3 = sum_B2 - sum_B * sum_B / (double)N;
	return M1 / sqrt(M2*M3);
}
void assign(artist&a, artist&b)
{
	a.acousticness = b.acousticness;
	a.danceability = b.danceability;
//	a.duration = b.duration;
	a.energy = b.energy;
	a.instrumentalness = b.instrumentalness;
//	a.key = b.key;
//	a.liveness = b.liveness;
//	a.loudness = b.loudness;
//	a.mode = b.mode;
//	a.popularity = b.popularity;
	a.speechiness = b.speechiness;
//    a.valence = b.valence;
//	a.tempo = b.tempo;
	a.label = b.label;
}
int main()
{
	ifstream file1("3.txt",ios::binary);
	if (!file1)
	{
		cout << "cannot open file!" << endl;
		exit(-1);
	}		

	/*while (!file1.eof())
	{	
		artist temp;
		file1 >> temp.id >>temp.danceability>>temp.energy>>temp.valence>>temp.tempo>>temp.loudness>>temp.mode>>temp.key>> temp.acousticness >> temp.instrumentalness>>temp.liveness>>temp.speechiness>>temp.duration>>temp.popularity>>temp.label;
		vec.push_back(temp);
	}*/
	while (!file1.eof())
	{
		artist temp;
		file1 >> temp.id >>temp.acousticness >> temp.instrumentalness>> temp.speechiness >> temp.energy >> temp.danceability >> temp.label;
		vec.push_back(temp);
	}
	file1.close();
	//cout << vec[20].acousticness << endl;
	artist art1, art2;
	
	ifstream file2("2.txt", ios::binary);
	ofstream file3("result_同类别有影响_降维后.txt");
	ofstream file4("result_不同类别有影响_降维后.txt");
	if (!file2)
	{
		cout << "cannot open file!" << endl;
		exit(-1);
	}
	if (!file3)
	{
		cout << "cannot open file!" << endl;
		exit(-1);
	}
	if (!file4)
	{
		cout << "cannot open file!" << endl;
		exit(-1);
	}

	double sum1 = 0,sum2=0;
	int count1 = 0,count2=0;
	while (!file2.eof())
	{
		int temp;
		file2 >> art2.id>>temp>>art1.id>>temp;
		vector<artist>::iterator it;
		it = find(vec.begin(), vec.end(), art1);
		assign(art1, *it);
		it=find(vec.begin(), vec.end(), art2);
		assign(art2, *it);
		if (art1.label == art2.label)
		{		
			double r = pearson(art1, art2);
			sum1 += r;
			file3<<"( "<<art1.id<<","<<art2.id<<" ): " <<r <<" ";
			count1++;
			if (count1 % 5 == 0)
				file3 << endl;
		}
		if (art1.label != art2.label)
		{
			double r = pearson(art1, art2);
			sum2 += r;
			file4 << "( " << art1.id << "," << art2.id << " ): " << r << " ";
			count2++;
			if (count2 % 5 == 0)
				file4 << endl;
		}
	}
	file3 << endl;
	file4 << endl;

	file3 << "average: " << sum1 /(double)count1<< endl;
	file4 << "average: " << sum2 / (double)count2 << endl;

	file2.close();
	file3.close();
	file4.close();
	/*ifstream file("3.txt");
	double sum=0;
	while (!file.eof())
	{
		file >> art1.id >> art2.id;
		vector<artist>::iterator it;
		it = find(vec.begin(), vec.end(), art1);
		assign(art1, *it);
		it = find(vec.begin(), vec.end(), art2);
		assign(art2, *it);
		double r = pearson(art1, art2);
		cout<< "( " << art1.id << "," << art2.id << " ): " << r << endl;
		sum += r;
	}
	cout << "average: " << sum / 4.0 << endl;*/
}