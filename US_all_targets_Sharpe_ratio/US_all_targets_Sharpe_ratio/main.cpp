/*���ѥ��ȫe20�j�B���ѥ��ȫe50�j�B�Dã30*/
/*�]���զX��,�O�o���������*/
/*�o��O�ήL���Ⱦɤ�*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <algorithm>
using namespace std;

ifstream input_file;
ifstream test_input_file;
ofstream output_file;
double all_stock[10000][10000]; //�Ҧ��Ѳ�
double test_all_stock[100][400];
string stock_no[50]; //�Ѳ��s��
string test_stock_no[50];
int index;
int test_index;
//read_file

const int partical_num = 10;
const int generation = 10000;
const int experiment_time = 50;
const int file_num = 8;
double beta[50];
int partical[partical_num][90000];
//int profolio[50];//���զX
//initial

int stock_index[10][50];//�O���C���ɤl(10)�ҿ�쪺���զX(50)
						//choose

int train_stock_index[50];
double initial_fund = 10000000; //��l���
double test_initial_fund;
double remaind;//�Ѿl���
double test_remaind;
double all_remain_fund;
double test_all_remain_fund;
double fund_standardization; //�������
double fee; //����O
double test_fee;
double total_fee[50000];
double one_fund_standardization[50][2500];
double n_fund_standardization[100][50][2500];//�U�ɸ������
double test_n_fund_standardization[50][300];//���մ��������
double partical_fund_standardization[100][2500];//���զX�������
double risk[10000]; //�C�魷�I
double test_risk;//�V�m���C�魷�I
double final_test_risk;
double m[10000]; //�w�����S
double test_m;
int share_money;//�C�ɤ��t����
int test_share_money;
double one_of_price; //�C�i����
double test_one_of_price;
double daily_risk[50][10000][10];//�C������C�N�C�魷�I
double expect_m[50][10000][10];//�C������C�N�w�����S
double Gbest_daily_risk;//�̨θѨC�魷�I
double Gbest_expect_retutn;//�̨θѹw�����S

int buy_lots;//�i�R���i��
int test_buy_lots;
double yi[10000][10000];//��i�ѯu��������
double test_yi[1000];
double all_final_yi[10000];//�C�@�Ӳɤl�̫�@�Ѫ�yi
						   //standardization

double m1;
int m2;
double all_standardization[2500];
double Yi[100][300];//�@���^�k�Ͷսu
double test_Yi[300];
double r1;
double trend_ratio;//�Ͷխ�
double test_trend_ratio;
double final_test_trend_ratio;
double all_trend_ratio[partical_num];
//fitness

double theta = 0.0004;
double min_fitness = 0;
double max_fitness = 0;
double max_fitness_aray[100];
int min_fitness_tmp = 0;
int max_fitness_tmp = 0;
int Gbest_tmp = 0;
int t;
//update


int i, j, k, a;
int kind[50];
//double n;
int n[partical_num];//��諸���զX���X��

int s_stock_index = 0;//train stock num
int test_stock_index = 0;

int total_n;
int day = 0;
int test_day;
//compare

double all_max = 0;
int all_max_solution[10000];
double random;
double Gbest[50];
double all_max_tmp[50];
double Gbest_max;
int best_experimrentime;
int best_generation;
//double real_all_trend_ratio[experiment_time][generation][partical_num];
double real_yi[experiment_time][generation][partical_num];
double Gbest_yi;
int Gbest_num;//Gbest���X�{����
int final_n[experiment_time][generation][partical_num];//�s�̨θ��ɼ�
int Gbest_n;//Gbest��쪺�ɼ�
int Gbest_i;
int selection_stock_no[partical_num][50];
int real_partical[50][partical_num][50];
string final_portfolio[50];
int all_buy_lots[50];//�s�i�R�i�ƪ��}�C
int last_test_all_buy_paper[50];
int test_all_buy_lots[50];
int all_share_money[partical_num];//�s���t������}�C
int test_all_share_money[partical_num];
int compare_share_money[experiment_time][generation][partical_num];//�s�C������C�ӥ@�N�C�Ӳɤl�����t����}�C
int compare_buy_lots[50][partical_num][50];//�s�C�ӹ��礤���զX�Ѳ��i�R�i��
int Gbest_share_money;
int Gbest_buy_lots[50];//Gbest�զX���Ѳ��i�R���i��
double real_all_remain_fund[50];
double test_real_all_remain_fund[50];
double compare_remain_fund[50][50];
double Gbest_all_remain_fund[50];//Gbest���R���U�ѳѾl���
double all_n_fund_standardization[50][50][300];
double Gbest_n_fund_standardization[50][300];
double all_total_yi[300];
double test_all_total_yi[300];
double test_all_final_fund;
double final_fund[10];
double compare_total_yi[50][300];
double real_total_yi[300];
int total_test_day;
double test_total_yi[200][10000];
double final_total_test_yi[10000];
double test_total_all_period_m;//���մ��`��w�����S
double test_all_period_Yi[10000];
double test_all_period_risk;
double test_all_period_trend_ratio;
double test_all_period_m1;
int test_all_period_m2;
double last_total_std[10000];//�s�Ҧ����մ��`�������
double last_total_Yi[10000];//�p���`����մ��w���������
double real_last_total_std[200][10000];//�s�Ҧ����մ��`�������
int day_count;
double all_test_m;
double final_all_test_m;//�`����մ��̲׹w�����S
double final_test_m1;
double final_test_m2;
double final_test_r1;
int day_count_risk;//�`����մ��p�⭷�I�Ѽ�counter
int day_count_result;//�`����մ���X���G�Ѽ�counter

double all_file_gbest_risk[200];//�V�m���U�϶����I
double all_file_gbest_return[200];//�V�m���U�϶��w�����S
double all_file_test_return[200];//���մ��Ӱ϶��w�����S
double all_file_test_risk[200];//���մ��U�϶����I

int all_file_gbest_num[200];
int all_file_gbest_generation[200];
int all_file_gbest_experiment[200];
int all_file_gbest_appear[200];
double all_gbest_trend_ratio[200];
double all_test_period_trend_ratio[200];
string all_file_gbest_portfolio[200][50];
string all_file_test_portfolio[200][50];

string AAPL[] = { "AAPL-2012.csv", "AAPL-2013.csv", "AAPL-2014.csv", "AAPL-2015.csv", "AAPL-2016.csv", "AAPL-2017.csv", "AAPL-2018.csv", "AAPL-2019.csv" };
string AMZN[] = { "AMZN-2012.csv", "AMZN-2013.csv", "AMZN-2014.csv", "AMZN-2015.csv", "AMZN-2016.csv", "AMZN-2017.csv", "AMZN-2018.csv", "AMZN-2019.csv" };
string BABA[] = { "BABA-2014.csv", "BABA-2015.csv", "BABA-2016.csv", "BABA-2017.csv", "BABA-2018.csv", "BABA-2019.csv" };
string BRKA[] = { "BRK-A-2012.csv", "BRK-A-2013.csv", "BRK-A-2014.csv", "BRK-A-2015.csv", "BRK-A-2016.csv", "BRK-A-2017.csv", "BRK-A-2018.csv", "BRK-A-2019.csv" };
string FB[] = { "FB-2013.csv", "FB-2014.csv", "FB-2015.csv", "FB-2016.csv", "FB-2017.csv", "FB-2018.csv", "FB-2019.csv" };
string GOOG[] = { "GOOG-2012.csv", "GOOG-2013.csv", "GOOG-2014.csv", "GOOG-2015.csv", "GOOG-2016.csv", "GOOG-2017.csv", "GOOG-2018.csv", "GOOG-2019.csv" };
string GOOGL[] = { "GOOGL-2012.csv", "GOOGL-2013.csv", "GOOGL-2014.csv", "GOOGL-2015.csv", "GOOGL-2016.csv", "GOOGL-2017.csv", "GOOGL-2018.csv", "GOOGL-2019.csv" };
string JNJ[] = { "JNJ-2012.csv", "JNJ-2013.csv", "JNJ-2014.csv", "JNJ-2015.csv", "JNJ-2016.csv", "JNJ-2017.csv", "JNJ-2018.csv", "JNJ-2019.csv" };
string JPM[] = { "JPM-2012.csv", "JPM-2013.csv", "JPM-2014.csv", "JPM-2015.csv", "JPM-2016.csv", "JPM-2017.csv", "JPM-2018.csv", "JPM-2019.csv" };
string MSFT[] = { "MSFT-2012.csv", "MSFT-2013.csv", "MSFT-2014.csv", "MSFT-2015.csv", "MSFT-2016.csv", "MSFT-2017.csv", "MSFT-2018.csv", "MSFT-2019.csv" };
string TCEHY[] = { "TCEHY_2012.csv", "TCEHY_2013.csv", "TCEHY_2014.csv", "TCEHY_2015.csv", "TCEHY_2016.csv", "TCEHY_2017.csv", "TCEHY_2018.csv", "TCEHY_2019.csv" };
string V[] = { "V-2012.csv", "V-2013.csv", "V-2014.csv", "V-2015.csv", "V-2016.csv", "V-2017.csv", "V-2018.csv", "V-2019.csv" };
string XOM[] = { "XOM-2012.csv", "XOM-2013.csv", "XOM-2014.csv", "XOM-2015.csv", "XOM-2016.csv", "XOM-2017.csv", "XOM-2018.csv", "XOM-2019.csv" };
string all_US_10[] = { "2012.csv", "2013.csv", "2014.csv", "2015.csv", "2016.csv", "2017.csv", "2018.csv", "2019.csv" };
string all_US_12[] = { "2012.csv", "2013.csv", "2014.csv", "2015.csv", "2016.csv", "2017.csv", "2018.csv", "2019.csv" };
/*���ѥ��ȫe12�j*/
string BRKB[] = { "BRK.B_2012.csv", "BRK.B_2013.csv", "BRK.B_2014.csv", "BRK.B_2015.csv", "BRK.B_2016.csv", "BRK.B_2017.csv", "BRK.B_2018.csv", "BRK.B_2019.csv" };
string CHT[] = { "CHT_2012.csv", "CHT_2013.csv", "CHT_2014.csv", "CHT_2015.csv", "CHT_2016.csv", "CHT_2017.csv", "CHT_2018.csv", "CHT_2019.csv" };
string HD[] = { "HD_2012.csv", "HD_2013.csv", "HD_2014.csv", "HD_2015.csv","HD_2016.csv","HD_2017.csv","HD_2018.csv","HD_2019.csv" };
string MA[] = { "MA_2012.csv","MA_2013.csv","MA_2014.csv","MA_2015.csv","MA_2016.csv","MA_2017.csv","MA_2018.csv","MA_2019.csv" };
string PG[] = { "PG_2012.csv", "PG_2013.csv","PG_2014.csv","PG_2015.csv","PG_2016.csv","PG_2017.csv","PG_2018.csv","PG_2019.csv" };
string SNP[] = { "SNP_2012.csv", "SNP_2013.csv", "SNP_2014.csv", "SNP_2015.csv", "SNP_2016.csv", "SNP_2017.csv", "SNP_2018.csv", "SNP_2019.csv" };
string T[] = { "T_2012.csv", "T_2013.csv", "T_2014.csv", "T_2015.csv", "T_2016.csv", "T_2017.csv", "T_2018.csv", "T_2019.csv" };
string TSM[] = { "TSM_2012.csv", "TSM_2013.csv", "TSM_2014.csv", "TSM_2015.csv", "TSM_2016.csv", "TSM_2017.csv", "TSM_2018.csv", "TSM_2019.csv" };
string UNH[] = { "UNH_2012.csv", "UNH_2013.csv", "UNH_2014.csv", "UNH_2015.csv", "UNH_2016.csv", "UNH_2017.csv", "UNH_2018.csv", "UNH_2019.csv" };
string VOD[] = { "VOD_2012.csv", "VOD_2013.csv", "VOD_2014.csv",  "VOD_2015.csv", "VOD_2016.csv", "VOD_2017.csv", "VOD_2018.csv", "VOD_2019.csv" };
string WMT[] = { "WMT_2012.csv", "WMT_2013.csv", "WMT_2014.csv", "WMT_2015.csv", "WMT_2016.csv", "WMT_2017.csv", "WMT_2018.csv", "WMT_2019.csv" };
/*���ѥ��ȫe20�j*/

string BAC[] = { "BAC_2012.csv",  "BAC_2013.csv", "BAC_2014.csv", "BAC_2015.csv", "BAC_2016.csv", "BAC_2017.csv", "BAC_2018.csv", "BAC_2019.csv" };
string CSCO[] = { "CSCO_2012.csv", "CSCO_2013.csv", "CSCO_2014.csv", "CSCO_2015.csv", "CSCO_2016.csv", "CSCO_2017.csv", "CSCO_2018.csv", "CSCO_2019.csv" };
string INTC[] = { "INTC_2012.csv", "INTC_2013.csv", "INTC_2014.csv", "INTC_2015.csv", "INTC_2016.csv", "INTC_2017.csv", "INTC_2018.csv", "INTC_2019.csv" };
string VZ[] = { "VZ_2012.csv", "VZ_2013.csv", "VZ_2014.csv", "VZ_2015.csv", "VZ_2016.csv", "VZ_2017.csv", "VZ_2018.csv", "VZ_2019.csv" };
string B_all_US_20[] = { "B_20_2012.csv", "B_20_2013.csv", "B_20_2014.csv", "B_20_2015.csv", "B_20_2016.csv", "B_20_2017.csv", "B_20_2018.csv", "B_20_2019.csv" };
string LG_all_US_20[] = { "LG_20_2012.csv", "LG_20_2013.csv", "LG_20_2014.csv", "LG_20_2015.csv", "LG_20_2016.csv", "LG_20_2017.csv", "LG_20_2018.csv", "LG_20_2019.csv" };
/*�T�{�L�᪺���ѥ��ȫe20�j*/

string Y2Y_train20[] = { "train_2012(2012 Q1).csv", "train_2013(2013 Q1).csv", "train_2014(2014 Q1).csv", "train_2015(2015 Q1).csv", "train_2016(2016 Q1).csv", "train_2017(2017 Q1).csv", "train_2018(2018 Q1).csv" };
string Y2Q_train20[] = { "train_2012(2012 Q1).csv", "train_2012_Q2~2013_Q1(2012 Q1).csv", "train_2012_Q3~2013_Q2(2012 Q1).csv", "train_2012_Q4~2013_Q3(2012 Q1).csv", "train_2013(2013 Q1).csv", "train_2013_Q2~2014_Q1(2013 Q1).csv",
"train_2013_Q3~2014_Q2(2013 Q1).csv", "train_2013_Q4~2014_Q3(2013 Q1).csv", "train_2014(2014 Q1).csv", "train_2014_Q2~2015_Q1(2014 Q1).csv", "train_2014_Q3~2015_Q2(2014 Q1).csv", "train_2014_Q4~2015_Q3(2014 Q1).csv", "train_2015(2015 Q1).csv",
"train_2015_Q2~2016_Q1(2015 Q1).csv", "train_2015_Q3~2016_Q2(2015 Q1).csv", "train_2015_Q4~2016_Q3(2015 Q1).csv", "train_2016(2016 Q1).csv", "train_2016_Q2~2017_Q1(2016 Q1).csv", "train_2016_Q3~2017_Q2(2016 Q1).csv", "train_2016_Q4~2017_Q3(2016 Q1).csv",
"train_2017(2017 Q1).csv", "train_2017_Q2~2018_Q1(2017 Q1).csv", "train_2017_Q3~2018_Q2(2017 Q1).csv", "train_2017_Q4~2018_Q3(2017 Q1).csv", "train_2018(2018 Q1).csv", "train_2018_Q2~2019_Q1(2018 Q1).csv", "train_2018_Q3~2019_Q2(2018 Q1).csv", "train_2018_Q4~2019_Q3(2018 Q1).csv" };
string Y2M_train20[] = { "train_2012(2012 Q1).csv", "train_2012_02~2013_01(2012 Q1).csv", "train_2012_03~2013_02(2012 Q1).csv", "train_2012_04~2013_03(2012 Q1).csv", "train_2012_05~2013_04(2012 Q1).csv", "train_2012_06~2013_05(2012 Q1).csv", "train_2012_07~2013_06(2012 Q1).csv", "train_2012_08~2013_07(2012 Q1).csv", "train_2012_09~2013_08(2012 Q1).csv", "train_2012_10~2013_09(2012 Q1).csv", "train_2012_11~2013_10(2012 Q1).csv", "train_2012_12~2013_11(2012 Q1).csv",
"train_2013(2013 Q1).csv", "train_2013_02~2014_01(2013 Q1).csv", "train_2013_03~2014_02(2013 Q1).csv", "train_2013_04~2014_03(2013 Q1).csv", "train_2013_05~2014_04(2013 Q1).csv", "train_2013_06~2014_05(2013 Q1).csv", "train_2013_07~2014_06(2013 Q1).csv", "train_2013_08~2014_07(2013 Q1).csv", "train_2013_09~2014_08(2013 Q1).csv", "train_2013_10~2014_09(2013 Q1).csv", "train_2013_11~2014_10(2013 Q1).csv", "train_2013_12~2014_11(2013 Q1).csv",
"train_2014(2014 Q1).csv", "train_2014_02~2015_01(2014 Q1).csv", "train_2014_03~2015_02(2014 Q1).csv", "train_2014_04~2015_03(2014 Q1).csv", "train_2014_05~2015_04(2014 Q1).csv", "train_2014_06~2015_05(2014 Q1).csv", "train_2014_07~2015_06(2014 Q1).csv", "train_2014_08~2015_07(2014 Q1).csv", "train_2014_09~2015_08(2014 Q1).csv", "train_2014_10~2015_09(2014 Q1).csv", "train_2014_11~2015_10(2014 Q1).csv", "train_2014_12~2015_11(2014 Q1).csv",
"train_2015(2015 Q1).csv", "train_2015_02~2016_01(2015 Q1).csv", "train_2015_03~2016_02(2015 Q1).csv", "train_2015_04~2016_03(2015 Q1).csv", "train_2015_05~2016_04(2015 Q1).csv", "train_2015_06~2016_05(2015 Q1).csv", "train_2015_07~2016_06(2015 Q1).csv", "train_2015_08~2016_07(2015 Q1).csv", "train_2015_09~2016_08(2015 Q1).csv", "train_2015_10~2016_09(2015 Q1).csv", "train_2015_11~2016_10(2015 Q1).csv", "train_2015_12~2016_11(2015 Q1).csv",
"train_2016(2016 Q1).csv", "train_2016_02~2017_01(2016 Q1).csv", "train_2016_03~2017_02(2016 Q1).csv", "train_2016_04~2017_03(2016 Q1).csv", "train_2016_05~2017_04(2016 Q1).csv", "train_2016_06~2017_05(2016 Q1).csv", "train_2016_07~2017_06(2016 Q1).csv", "train_2016_08~2017_07(2016 Q1).csv", "train_2016_09~2017_08(2016 Q1).csv", "train_2016_10~2017_09(2016 Q1).csv", "train_2016_11~2017_10(2016 Q1).csv", "train_2016_12~2017_11(2016 Q1).csv",
"train_2017(2017 Q1).csv", "train_2017_02~2018_01(2017 Q1).csv", "train_2017_03~2018_02(2017 Q1).csv", "train_2017_04~2018_03(2017 Q1).csv", "train_2017_05~2018_04(2017 Q1).csv", "train_2017_06~2018_05(2017 Q1).csv", "train_2017_07~2018_06(2017 Q1).csv", "train_2017_08~2018_07(2017 Q1).csv", "train_2017_09~2018_08(2017 Q1).csv", "train_2017_10~2018_09(2017 Q1).csv", "train_2017_11~2018_10(2017 Q1).csv", "train_2017_12~2018_11(2017 Q1).csv",
"train_2018(2018 Q1).csv", "train_2018_02~2019_01(2018 Q1).csv", "train_2018_03~2019_02(2018 Q1).csv", "train_2018_04~2019_03(2018 Q1).csv", "train_2018_05~2019_04(2018 Q1).csv", "train_2018_06~2019_05(2018 Q1).csv", "train_2018_07~2019_06(2018 Q1).csv", "train_2018_08~2019_07(2018 Q1).csv", "train_2018_09~2019_08(2018 Q1).csv", "train_2018_10~2019_09(2018 Q1).csv", "train_2018_11~2019_10(2018 Q1).csv", "train_2018_12~2019_11(2018 Q1).csv" };
string Y2H_train20[] = { "train_2012(2012 Q1).csv", "train_2012_Q3~2013_Q2(2012 Q1).csv", "train_2013(2013 Q1).csv", "train_2013_Q3~2014_Q2(2013 Q1).csv", "train_2014(2014 Q1).csv", "train_2014_Q3~2015_Q2(2014 Q1).csv", "train_2015(2015 Q1).csv", "train_2015_Q3~2016_Q2(2015 Q1).csv",
"train_2016(2016 Q1).csv", "train_2016_Q3~2017_Q2(2016 Q1).csv", "train_2017(2017 Q1).csv", "train_2017_Q3~2018_Q2(2017 Q1).csv", "train_2018(2018 Q1).csv", "train_2018_Q3~2019_Q2(2018 Q1).csv" };
string Q2Q_train20[] = { "train_2012_Q4(2012 Q1).csv", "train_2013_Q1(2013 Q1).csv", "train_2013_Q2(2013 Q1).csv", "train_2013_Q3(2013 Q1).csv", "train_2013_Q4(2013 Q1).csv", "train_2014_Q1(2014 Q1).csv", "train_2014_Q2(2014 Q1).csv", "train_2014_Q3(2014 Q1).csv", "train_2014_Q4(2014 Q1).csv", "train_2015_Q1(2015 Q1).csv", "train_2015_Q2(2015 Q1).csv", "train_2015_Q3(2015 Q1).csv", "train_2015_Q4(2015 Q1).csv", "train_2016_Q1(2016 Q1).csv", "train_2016_Q2(2016 Q1).csv",
"train_2016_Q3(2016 Q1).csv", "train_2016_Q4(2016 Q1).csv", "train_2017_Q1(2017 Q1).csv", "train_2017_Q2(2017 Q1).csv", "train_2017_Q3(2017 Q1).csv", "train_2017_Q4(2017 Q1).csv", "train_2018_Q1(2018 Q1).csv", "train_2018_Q2(2018 Q1).csv", "train_2018_Q3(2018 Q1).csv", "train_2018_Q4(2018 Q1).csv", "train_2019_Q1(2019 Q1).csv", "train_2019_Q2(2019 Q1).csv", "train_2019_Q3(2019 Q1).csv" };
string Q2M_train20[] = { "train_2012_10-12(2012 Q1).csv", "train_2012_11~2013_01(2012 Q1).csv", "train_2012_12~2013_02(2012 Q1).csv", "train_2013_01-03(2013 Q1).csv", "train_2013_02-04(2013 Q1).csv", "train_2013_03-05(2013 Q1).csv",
"train_2013_04-06(2013 Q1).csv", "train_2013_05-07(2013 Q1).csv", "train_2013_06-08(2013 Q1).csv", "train_2013_07-09(2013 Q1).csv", "train_2013_08-10(2013 Q1).csv", "train_2013_09-11(2013 Q1).csv", "train_2013_10-12(2013 Q1).csv", "train_2013_11~2014_01(2013 Q1).csv", "train_2013_12~2014_02(2013 Q1).csv", "train_2014_01-03(2014 Q1).csv", "train_2014_02-04(2014 Q1).csv", "train_2014_03-05(2014 Q1).csv", "train_2014_04-06(2014 Q1).csv", "train_2014_05-07(2014 Q1).csv",
"train_2014_06-08(2014 Q1).csv", "train_2014_07-09(2014 Q1).csv", "train_2014_08-10(2014 Q1).csv", "train_2014_09-11(2014 Q1).csv", "train_2014_10-12(2014 Q1).csv", "train_2014_11~2015_01(2014 Q1).csv", "train_2014_12~2015_02(2014 Q1).csv", "train_2015_01-03(2015 Q1).csv", "train_2015_02-04(2015 Q1).csv", "train_2015_03-05(2015 Q1).csv", "train_2015_04-06(2015 Q1).csv", "train_2015_05-07(2015 Q1).csv", "train_2015_06-08(2015 Q1).csv", "train_2015_07-09(2015 Q1).csv",
"train_2015_08-10(2015 Q1).csv", "train_2015_09-11(2015 Q1).csv", "train_2015_10-12(2015 Q1).csv", "train_2015_11~2016_01(2015 Q1).csv", "train_2015_12~2016_02(2015 Q1).csv", "train_2016_01-03(2016 Q1).csv", "train_2016_02-04(2016 Q1).csv", "train_2016_03-05(2016 Q1).csv", "train_2016_04-06(2016 Q1).csv", "train_2016_05-07(2016 Q1).csv", "train_2016_06-08(2016 Q1).csv", "train_2016_07-09(2016 Q1).csv", "train_2016_08-10(2016 Q1).csv", "train_2016_09-11(2016 Q1).csv",
"train_2016_10-12(2016 Q1).csv", "train_2016_11~2017_01(2016 Q1).csv", "train_2016_12~2017_02(2016 Q1).csv", "train_2017_01-03(2017 Q1).csv", "train_2017_02-04(2017 Q1).csv", "train_2017_03-05(2017 Q1).csv", "train_2017_04-06(2017 Q1).csv", "train_2017_05-07(2017 Q1).csv", "train_2017_06-08(2017 Q1).csv", "train_2017_07-09(2017 Q1).csv", "train_2017_08-10(2017 Q1).csv", "train_2017_09-11(2017 Q1).csv", "train_2017_10-12(2017 Q1).csv", "train_2017_11~2018_01(2017 Q1).csv",
"train_2017_12~2018_02(2017 Q1).csv", "train_2018_01-03(2018 Q1).csv", "train_2018_02-04(2018 Q1).csv", "train_2018_03-05(2018 Q1).csv", "train_2018_04-06(2018 Q1).csv", "train_2018_05-07(2018 Q1).csv", "train_2018_06-08(2018 Q1).csv", "train_2018_07-09(2018 Q1).csv", "train_2018_08-10(2018 Q1).csv", "train_2018_09-11(2018 Q1).csv", "train_2018_10-12(2018 Q1).csv", "train_2018_11~2019_01(2018 Q1).csv", "train_2018_12~2019_02(2018 Q1).csv", "train_2019_01-03(2019 Q1).csv", "train_2019_02-04(2019 Q1).csv",
"train_2019_03-05(2019 Q1).csv", "train_2019_04-06(2019 Q1).csv", "train_2019_05-07(2019 Q1).csv", "train_2019_06-08(2019 Q1).csv", "train_2019_07-09(2019 Q1).csv", "train_2019_08-10(2019 Q1).csv", "train_2019_09-11(2019 Q1).csv" };
string QQ_train20[] = { "train_2012_Q1(2012 Q1).csv", "train_2012_Q2(2012 Q1).csv", "train_2012_Q3(2012 Q1).csv", "train_2012_Q4(2012 Q1).csv", "train_2013_Q1(2013 Q1).csv", "train_2013_Q2(2013 Q1).csv", "train_2013_Q3(2013 Q1).csv", "train_2013_Q4(2013 Q1).csv", "train_2014_Q1(2014 Q1).csv", "train_2014_Q2(2014 Q1).csv", "train_2014_Q3(2014 Q1).csv", "train_2014_Q4(2014 Q1).csv", "train_2015_Q1(2015 Q1).csv", "train_2015_Q2(2015 Q1).csv", "train_2015_Q3(2015 Q1).csv", "train_2015_Q4(2015 Q1).csv",
"train_2016_Q1(2016 Q1).csv", "train_2016_Q2(2016 Q1).csv", "train_2016_Q3(2016 Q1).csv", "train_2016_Q4(2016 Q1).csv", "train_2017_Q1(2017 Q1).csv", "train_2017_Q2(2017 Q1).csv", "train_2017_Q3(2017 Q1).csv", "train_2017_Q4(2017 Q1).csv", "train_2018_Q1(2018 Q1).csv", "train_2018_Q2(2018 Q1).csv", "train_2018_Q3(2018 Q1).csv", "train_2018_Q4(2018 Q1).csv" };
string M2M_train20[] = { "train_2012_12(2012 Q1).csv", "train_2013_01(2013 Q1).csv", "train_2013_02(2013 Q1).csv", "train_2013_03(2013 Q1).csv", "train_2013_04(2013 Q1).csv", "train_2013_05(2013 Q1).csv",
"train_2013_06(2013 Q1).csv", "train_2013_07(2013 Q1).csv", "train_2013_08(2013 Q1).csv", "train_2013_09(2013 Q1).csv", "train_2013_10(2013 Q1).csv", "train_2013_11(2013 Q1).csv", "train_2013_12(2013 Q1).csv", "train_2014_01(2014 Q1).csv", "train_2014_02(2014 Q1).csv", "train_2014_03(2014 Q1).csv", "train_2014_04(2014 Q1).csv", "train_2014_05(2014 Q1).csv", "train_2014_06(2014 Q1).csv", "train_2014_07(2014 Q1).csv",
"train_2014_08(2014 Q1).csv", "train_2014_09(2014 Q1).csv", "train_2014_10(2014 Q1).csv", "train_2014_11(2014 Q1).csv", "train_2014_12(2014 Q1).csv", "train_2015_01(2015 Q1).csv", "train_2015_02(2015 Q1).csv", "train_2015_03(2015 Q1).csv", "train_2015_04(2015 Q1).csv", "train_2015_05(2015 Q1).csv", "train_2015_06(2015 Q1).csv", "train_2015_07(2015 Q1).csv", "train_2015_08(2015 Q1).csv", "train_2015_09(2015 Q1).csv",
"train_2015_10(2015 Q1).csv", "train_2015_11(2015 Q1).csv", "train_2015_12(2015 Q1).csv", "train_2016_01(2016 Q1).csv", "train_2016_02(2016 Q1).csv", "train_2016_03(2016 Q1).csv", "train_2016_04(2016 Q1).csv", "train_2016_05(2016 Q1).csv", "train_2016_06(2016 Q1).csv", "train_2016_07(2016 Q1).csv", "train_2016_08(2016 Q1).csv", "train_2016_09(2016 Q1).csv", "train_2016_10(2016 Q1).csv", "train_2016_11(2016 Q1).csv",
"train_2016_12(2016 Q1).csv", "train_2017_01(2017 Q1).csv", "train_2017_02(2017 Q1).csv", "train_2017_03(2017 Q1).csv", "train_2017_04(2017 Q1).csv", "train_2017_05(2017 Q1).csv", "train_2017_06(2017 Q1).csv", "train_2017_07(2017 Q1).csv", "train_2017_08(2017 Q1).csv", "train_2017_09(2017 Q1).csv", "train_2017_10(2017 Q1).csv", "train_2017_11(2017 Q1).csv", "train_2017_12(2017 Q1).csv", "train_2018_01(2018 Q1).csv",
"train_2018_02(2018 Q1).csv", "train_2018_03(2018 Q1).csv", "train_2018_04(2018 Q1).csv", "train_2018_05(2018 Q1).csv", "train_2018_06(2018 Q1).csv", "train_2018_07(2018 Q1).csv", "train_2018_08(2018 Q1).csv", "train_2018_09(2018 Q1).csv", "train_2018_10(2018 Q1).csv", "train_2018_11(2018 Q1).csv", "train_2018_12(2018 Q1).csv", "train_2019_01(2019 Q1).csv", "train_2019_02(2019 Q1).csv", "train_2019_03(2019 Q1).csv",
"train_2019_04(2019 Q1).csv", "train_2019_05(2019 Q1).csv", "train_2019_06(2019 Q1).csv", "train_2019_07(2019 Q1).csv", "train_2019_08(2019 Q1).csv", "train_2019_09(2019 Q1).csv", "train_2019_10(2019 Q1).csv", "train_2019_11(2019 Q1).csv" };
string MM_train20[] = { "train_2012_01(2012 Q1).csv", "train_2012_02(2012 Q1).csv", "train_2012_03(2012 Q1).csv", "train_2012_04(2012 Q1).csv", "train_2012_05(2012 Q1).csv", "train_2012_06(2012 Q1).csv", "train_2012_07(2012 Q1).csv", "train_2012_08(2012 Q1).csv", "train_2012_09(2012 Q1).csv", "train_2012_10(2012 Q1).csv", "train_2012_11(2012 Q1).csv", "train_2012_12(2012 Q1).csv", "train_2013_01(2013 Q1).csv", "train_2013_02(2013 Q1).csv", "train_2013_03(2013 Q1).csv",
"train_2013_04(2013 Q1).csv", "train_2013_05(2013 Q1).csv", "train_2013_06(2013 Q1).csv", "train_2013_07(2013 Q1).csv", "train_2013_08(2013 Q1).csv", "train_2013_09(2013 Q1).csv", "train_2013_10(2013 Q1).csv", "train_2013_11(2013 Q1).csv", "train_2013_12(2013 Q1).csv", "train_2014_01(2014 Q1).csv", "train_2014_02(2014 Q1).csv", "train_2014_03(2014 Q1).csv", "train_2014_04(2014 Q1).csv", "train_2014_05(2014 Q1).csv", "train_2014_06(2014 Q1).csv", "train_2014_07(2014 Q1).csv", "train_2014_08(2014 Q1).csv",
"train_2014_09(2014 Q1).csv", "train_2014_10(2014 Q1).csv", "train_2014_11(2014 Q1).csv", "train_2014_12(2014 Q1).csv", "train_2015_01(2015 Q1).csv", "train_2015_02(2015 Q1).csv", "train_2015_03(2015 Q1).csv", "train_2015_04(2015 Q1).csv", "train_2015_05(2015 Q1).csv", "train_2015_06(2015 Q1).csv", "train_2015_07(2015 Q1).csv", "train_2015_08(2015 Q1).csv", "train_2015_09(2015 Q1).csv", "train_2015_10(2015 Q1).csv", "train_2015_11(2015 Q1).csv", "train_2015_12(2015 Q1).csv", "train_2016_01(2016 Q1).csv",
"train_2016_02(2016 Q1).csv", "train_2016_03(2016 Q1).csv", "train_2016_04(2016 Q1).csv", "train_2016_05(2016 Q1).csv", "train_2016_06(2016 Q1).csv", "train_2016_07(2016 Q1).csv", "train_2016_08(2016 Q1).csv", "train_2016_09(2016 Q1).csv", "train_2016_10(2016 Q1).csv", "train_2016_11(2016 Q1).csv", "train_2016_12(2016 Q1).csv", "train_2017_01(2017 Q1).csv", "train_2017_02(2017 Q1).csv", "train_2017_03(2017 Q1).csv", "train_2017_04(2017 Q1).csv", "train_2017_05(2017 Q1).csv", "train_2017_06(2017 Q1).csv",
"train_2017_07(2017 Q1).csv", "train_2017_08(2017 Q1).csv", "train_2017_09(2017 Q1).csv", "train_2017_10(2017 Q1).csv", "train_2017_11(2017 Q1).csv", "train_2017_12(2017 Q1).csv", "train_2018_01(2018 Q1).csv", "train_2018_02(2018 Q1).csv", "train_2018_03(2018 Q1).csv", "train_2018_04(2018 Q1).csv", "train_2018_05(2018 Q1).csv", "train_2018_06(2018 Q1).csv", "train_2018_07(2018 Q1).csv", "train_2018_08(2018 Q1).csv", "train_2018_09(2018 Q1).csv", "train_2018_10(2018 Q1).csv", "train_2018_11(2018 Q1).csv",
"train_2018_12(2018 Q1).csv" };
string H2Q_train20[] = { "train_2012_Q3-Q4(2012 Q1).csv", "train_2012_Q4~2013_Q1(2012 Q1).csv", "train_2013_Q1-Q2(2013 Q1).csv", "train_2013_Q2-Q3(2013 Q1).csv", "train_2013_Q3-Q4(2013 Q1).csv", "train_2013_Q4~2014_Q1(2013 Q1).csv", "train_2014_Q1-Q2(2014 Q1).csv", "train_2014_Q2-Q3(2014 Q1).csv", "train_2014_Q3-Q4(2014 Q1).csv", "train_2014_Q4~2015_Q1(2014 Q1).csv", "train_2015_Q1-Q2(2015 Q1).csv", "train_2015_Q2-Q3(2015 Q1).csv", "train_2015_Q3-Q4(2015 Q1).csv", "train_2015_Q4~2016_Q1(2015 Q1).csv", "train_2016_Q1-Q2(2016 Q1).csv", "train_2016_Q2-Q3(2016 Q1).csv",
"train_2016_Q3-Q4(2016 Q1).csv", "train_2016_Q4~2017_Q1(2016 Q1).csv", "train_2017_Q1-Q2(2017 Q1).csv", "train_2017_Q2-Q3(2017 Q1).csv", "train_2017_Q3-Q4(2017 Q1).csv", "train_2017_Q4~2018_Q1(2017 Q1).csv", "train_2018_Q1-Q2(2018 Q1).csv", "train_2018_Q2-Q3(2018 Q1).csv", "train_2018_Q3-Q4(2018 Q1).csv", "train_2018_Q4~2019_Q1(2018 Q1).csv", "train_2019_Q1-Q2(2019 Q1).csv", "train_2019_Q2-Q3(2019 Q1).csv" };
string H2M_train20[] = { "train_2012_07-12(2012 Q1).csv", "train_2012_08~2013_01(2012 Q1).csv", "train_2012_09~2013_02(2012 Q1).csv",
"train_2012_10~2013_03(2012 Q1).csv", "train_2012_11~2013_04(2012 Q1).csv", "train_2012_12~2013_05(2012 Q1).csv", "train_2013_01-06(2013 Q1).csv", "train_2013_02-07(2013 Q1).csv", "train_2013_03-08(2013 Q1).csv", "train_2013_04-09(2013 Q1).csv", "train_2013_05-10(2013 Q1).csv", "train_2013_06-11(2013 Q1).csv", "train_2013_07-12(2013 Q1).csv", "train_2013_08~2014_01(2013 Q1).csv", "train_2013_09~2014_02(2013 Q1).csv",
"train_2013_10~2014_03(2013 Q1).csv", "train_2013_11~2014_04(2013 Q1).csv", "train_2013_12~2014_05(2013 Q1).csv", "train_2014_01-06(2014 Q1).csv", "train_2014_02-07(2014 Q1).csv", "train_2014_03-08(2014 Q1).csv", "train_2014_04-09(2014 Q1).csv", "train_2014_05-10(2014 Q1).csv", "train_2014_06-11(2014 Q1).csv", "train_2014_07-12(2014 Q1).csv", "train_2014_08~2015_01(2014 Q1).csv", "train_2014_09~2015_02(2014 Q1).csv", "train_2014_10~2015_03(2014 Q1).csv",
"train_2014_11~2015_04(2014 Q1).csv", "train_2014_12~2015_05(2014 Q1).csv", "train_2015_01-06(2015 Q1).csv", "train_2015_02-07(2015 Q1).csv", "train_2015_03-08(2015 Q1).csv", "train_2015_04-09(2015 Q1).csv", "train_2015_05-10(2015 Q1).csv", "train_2015_06-11(2015 Q1).csv", "train_2015_07-12(2015 Q1).csv", "train_2015_08~2016_01(2015 Q1).csv", "train_2015_09~2016_02(2015 Q1).csv", "train_2015_10~2016_03(2015 Q1).csv", "train_2015_11~2016_04(2015 Q1).csv",
"train_2015_12~2016_05(2015 Q1).csv", "train_2016_01-06(2016 Q1).csv", "train_2016_02-07(2016 Q1).csv", "train_2016_03-08(2016 Q1).csv", "train_2016_04-09(2016 Q1).csv", "train_2016_05-10(2016 Q1).csv", "train_2016_06-11(2016 Q1).csv", "train_2016_07-12(2016 Q1).csv", "train_2016_08~2017_01(2016 Q1).csv", "train_2016_09~2017_02(2016 Q1).csv", "train_2016_10~2017_03(2016 Q1).csv", "train_2016_11~2017_04(2016 Q1).csv", "train_2016_12~2017_05(2016 Q1).csv",
"train_2017_01-06(2017 Q1).csv", "train_2017_02-07(2017 Q1).csv", "train_2017_03-08(2017 Q1).csv", "train_2017_04-09(2017 Q1).csv", "train_2017_05-10(2017 Q1).csv", "train_2017_06-11(2017 Q1).csv", "train_2017_07-12(2017 Q1).csv", "train_2017_08~2018_01(2017 Q1).csv", "train_2017_09~2018_02(2017 Q1).csv", "train_2017_10~2018_03(2017 Q1).csv", "train_2017_11~2018_04(2017 Q1).csv", "train_2017_12~2018_05(2017 Q1).csv", "train_2018_01-06(2018 Q1).csv",
"train_2018_02-07(2018 Q1).csv", "train_2018_03-08(2018 Q1).csv", "train_2018_04-09(2018 Q1).csv", "train_2018_05-10(2018 Q1).csv", "train_2018_06-11(2018 Q1).csv", "train_2018_07-12(2018 Q1).csv", "train_2018_08~2019_01(2018 Q1).csv", "train_2018_09~2019_02(2018 Q1).csv", "train_2018_10~2019_03(2018 Q1).csv", "train_2018_11~2019_04(2018 Q1).csv", "train_2018_12~2019_05(2018 Q1).csv", "train_2019_01-06(2019 Q1).csv", "train_2019_02-07(2019 Q1).csv",
"train_2019_03-08(2019 Q1).csv", "train_2019_04-09(2019 Q1).csv", "train_2019_05-10(2019 Q1).csv", "train_2019_06-11(2019 Q1).csv" };
string HH_train20[] = { "train_2012_Q1-Q2(2012 Q1).csv", "train_2012_Q3-Q4(2012 Q1).csv", "train_2013_Q1-Q2(2013 Q1).csv", "train_2013_Q3-Q4(2013 Q1).csv", "train_2014_Q1-Q2(2014 Q1).csv", "train_2014_Q3-Q4(2014 Q1).csv", "train_2015_Q1-Q2(2015 Q1).csv", "train_2015_Q3-Q4(2015 Q1).csv", "train_2016_Q1-Q2(2016 Q1).csv", "train_2016_Q3-Q4(2016 Q1).csv", "train_2017_Q1-Q2(2017 Q1).csv", "train_2017_Q3-Q4(2017 Q1).csv", "train_2018_Q1-Q2(2018 Q1).csv", "train_2018_Q3-Q4(2018 Q1).csv" };
string H2H_train20[] = { "train_2012_Q3-Q4(2012 Q1).csv", "train_2013_Q1-Q2(2013 Q1).csv", "train_2013_Q3-Q4(2013 Q1).csv", "train_2014_Q1-Q2(2014 Q1).csv", "train_2014_Q3-Q4(2014 Q1).csv", "train_2015_Q1-Q2(2015 Q1).csv", "train_2015_Q3-Q4(2015 Q1).csv", "train_2016_Q1-Q2(2016 Q1).csv","train_2016_Q3-Q4(2016 Q1).csv","train_2017_Q1-Q2(2017 Q1).csv", "train_2017_Q3-Q4(2017 Q1).csv", "train_2018_Q1-Q2(2018 Q1).csv", "train_2018_Q3-Q4(2018 Q1).csv", "train_2019_Q1-Q2(2019 Q1).csv" };
/*���ȫe20�j�V�m��*/

string Y2Y_test20[] = { "test_2013(2012 Q1).csv", "test_2014(2013 Q1).csv", "test_2015(2014 Q1).csv", "test_2016(2015 Q1).csv", "test_2017(2016 Q1).csv", "test_2018(2017 Q1).csv", "test_2019(2018 Q1).csv" };
string Y2Q_test20[] = { "test_2013_Q1(2012 Q1).csv", "test_2013_Q2(2012 Q1).csv", "test_2013_Q3(2012 Q1).csv", "test_2013_Q4(2012 Q1).csv", "test_2014_Q1(2013 Q1).csv","test_2014_Q2(2013 Q1).csv", "test_2014_Q3(2013 Q1).csv", "test_2014_Q4(2013 Q1).csv", "test_2015_Q1(2014 Q1).csv", "test_2015_Q2(2014 Q1).csv", "test_2015_Q3(2014 Q1).csv", "test_2015_Q4(2014 Q1).csv", "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2015 Q1).csv", "test_2016_Q3(2015 Q1).csv", "test_2016_Q4(2015 Q1).csv",
"test_2017_Q1(2016 Q1).csv", "test_2017_Q2(2016 Q1).csv", "test_2017_Q3(2016 Q1).csv", "test_2017_Q4(2016 Q1).csv", "test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2017 Q1).csv", "test_2018_Q3(2017 Q1).csv", "test_2018_Q4(2017 Q1).csv", "test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2018 Q1).csv", "test_2019_Q3(2018 Q1).csv", "test_2019_Q4(2018 Q1).csv" };
string Y2M_test20[] = { "test_2013_01(2012 Q1).csv", "test_2013_02(2012 Q1).csv", "test_2013_03(2012 Q1).csv", "test_2013_04(2012 Q1).csv", "test_2013_05(2012 Q1).csv", "test_2013_06(2012 Q1).csv", "test_2013_07(2012 Q1).csv", "test_2013_08(2012 Q1).csv", "test_2013_09(2012 Q1).csv", "test_2013_10(2012 Q1).csv", "test_2013_11(2012 Q1).csv", "test_2013_12(2012 Q1).csv", "test_2014_01(2013 Q1).csv", "test_2014_02(2013 Q1).csv", "test_2014_03(2013 Q1).csv", "test_2014_04(2013 Q1).csv", "test_2014_05(2013 Q1).csv",
"test_2014_06(2013 Q1).csv", "test_2014_07(2013 Q1).csv", "test_2014_08(2013 Q1).csv", "test_2014_09(2013 Q1).csv", "test_2014_10(2013 Q1).csv", "test_2014_11(2013 Q1).csv", "test_2014_12(2013 Q1).csv", "test_2015_01(2014 Q1).csv", "test_2015_02(2014 Q1).csv", "test_2015_03(2014 Q1).csv", "test_2015_04(2014 Q1).csv", "test_2015_05(2014 Q1).csv", "test_2015_06(2014 Q1).csv", "test_2015_07(2014 Q1).csv", "test_2015_08(2014 Q1).csv", "test_2015_09(2014 Q1).csv", "test_2015_10(2014 Q1).csv", "test_2015_11(2014 Q1).csv",
"test_2015_12(2014 Q1).csv", "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv", "test_2016_04(2015 Q1).csv", "test_2016_05(2015 Q1).csv", "test_2016_06(2015 Q1).csv", "test_2016_07(2015 Q1).csv", "test_2016_08(2015 Q1).csv", "test_2016_09(2015 Q1).csv", "test_2016_10(2015 Q1).csv", "test_2016_11(2015 Q1).csv", "test_2016_12(2015 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2016 Q1).csv", "test_2017_05(2016 Q1).csv",
"test_2017_06(2016 Q1).csv", "test_2017_07(2016 Q1).csv", "test_2017_08(2016 Q1).csv", "test_2017_09(2016 Q1).csv", "test_2017_10(2016 Q1).csv", "test_2017_11(2016 Q1).csv", "test_2017_12(2016 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2017 Q1).csv", "test_2018_05(2017 Q1).csv", "test_2018_06(2017 Q1).csv", "test_2018_07(2017 Q1).csv", "test_2018_08(2017 Q1).csv", "test_2018_09(2017 Q1).csv", "test_2018_10(2017 Q1).csv", "test_2018_11(2017 Q1).csv",
"test_2018_12(2017 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2018 Q1).csv", "test_2019_05(2018 Q1).csv", "test_2019_06(2018 Q1).csv", "test_2019_07(2018 Q1).csv", "test_2019_08(2018 Q1).csv", "test_2019_09(2018 Q1).csv", "test_2019_10(2018 Q1).csv", "test_2019_11(2018 Q1).csv", "test_2019_12(2018 Q1).csv" };
string Y2H_test20[] = { "test_2013_Q1-Q2(2012 Q1).csv", "test_2013_Q3-Q4(2012 Q1).csv", "test_2014_Q1-Q2(2013 Q1).csv", "test_2014_Q3-Q4(2013 Q1).csv", "test_2015_Q1-Q2(2014 Q1).csv", "test_2015_Q3-Q4(2014 Q1).csv", "test_2016_Q1-Q2(2015 Q1).csv", "test_2016_Q3-Q4(2015 Q1).csv", "test_2017_Q1-Q2(2016 Q1).csv", "test_2017_Q3-Q4(2016 Q1).csv", "test_2018_Q1-Q2(2017 Q1).csv", "test_2018_Q3-Q4(2017 Q1).csv", "test_2019_Q1-Q2(2018 Q1).csv", "test_2019_Q3-Q4(2018 Q1).csv" };
string Q2Q_test20[] = { "test_2013_Q1(2012 Q1).csv", "test_2013_Q2(2013 Q1).csv", "test_2013_Q3(2013 Q1).csv", "test_2013_Q4(2013 Q1).csv", "test_2014_Q1(2013 Q1).csv", "test_2014_Q2(2014 Q1).csv", "test_2014_Q3(2014 Q1).csv", "test_2014_Q4(2014 Q1).csv", "test_2015_Q1(2014 Q1).csv", "test_2015_Q2(2015 Q1).csv", "test_2015_Q3(2015 Q1).csv", "test_2015_Q4(2015 Q1).csv", "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2016 Q1).csv", "test_2016_Q3(2016 Q1).csv", "test_2016_Q4(2016 Q1).csv", "test_2017_Q1(2016 Q1).csv",
"test_2017_Q2(2017 Q1).csv", "test_2017_Q3(2017 Q1).csv", "test_2017_Q4(2017 Q1).csv", "test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2018 Q1).csv", "test_2018_Q3(2018 Q1).csv", "test_2018_Q4(2018 Q1).csv", "test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2019 Q1).csv", "test_2019_Q3(2019 Q1).csv", "test_2019_Q4(2019 Q1).csv" };
string Q2M_test20[] = { "test_2013_01(2012 Q1).csv","test_2013_02(2012 Q1).csv", "test_2013_03(2012 Q1).csv", "test_2013_04(2013 Q1).csv", "test_2013_05(2013 Q1).csv", "test_2013_06(2013 Q1).csv", "test_2013_07(2013 Q1).csv", "test_2013_08(2013 Q1).csv", "test_2013_09(2013 Q1).csv", "test_2013_10(2013 Q1).csv", "test_2013_11(2013 Q1).csv", "test_2013_12(2013 Q1).csv", "test_2014_01(2013 Q1).csv", "test_2014_02(2013 Q1).csv", "test_2014_03(2013 Q1).csv", "test_2014_04(2014 Q1).csv", "test_2014_05(2014 Q1).csv", "test_2014_06(2014 Q1).csv", "test_2014_07(2014 Q1).csv", "test_2014_08(2014 Q1).csv",
"test_2014_09(2014 Q1).csv", "test_2014_10(2014 Q1).csv", "test_2014_11(2014 Q1).csv", "test_2014_12(2014 Q1).csv", "test_2015_01(2014 Q1).csv", "test_2015_02(2014 Q1).csv", "test_2015_03(2014 Q1).csv", "test_2015_04(2015 Q1).csv", "test_2015_05(2015 Q1).csv", "test_2015_06(2015 Q1).csv", "test_2015_07(2015 Q1).csv", "test_2015_08(2015 Q1).csv", "test_2015_09(2015 Q1).csv", "test_2015_10(2015 Q1).csv", "test_2015_11(2015 Q1).csv", "test_2015_12(2015 Q1).csv", "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv",
"test_2016_04(2016 Q1).csv", "test_2016_05(2016 Q1).csv", "test_2016_06(2016 Q1).csv", "test_2016_07(2016 Q1).csv", "test_2016_08(2016 Q1).csv", "test_2016_09(2016 Q1).csv", "test_2016_10(2016 Q1).csv", "test_2016_11(2016 Q1).csv", "test_2016_12(2016 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2017 Q1).csv", "test_2017_05(2017 Q1).csv", "test_2017_06(2017 Q1).csv", "test_2017_07(2017 Q1).csv", "test_2017_08(2017 Q1).csv", "test_2017_09(2017 Q1).csv", "test_2017_10(2017 Q1).csv",
"test_2017_11(2017 Q1).csv", "test_2017_12(2017 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2018 Q1).csv", "test_2018_05(2018 Q1).csv", "test_2018_06(2018 Q1).csv", "test_2018_07(2018 Q1).csv", "test_2018_08(2018 Q1).csv", "test_2018_09(2018 Q1).csv", "test_2018_10(2018 Q1).csv", "test_2018_11(2018 Q1).csv", "test_2018_12(2018 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2019 Q1).csv", "test_2019_05(2019 Q1).csv",
"test_2019_06(2019 Q1).csv", "test_2019_07(2019 Q1).csv", "test_2019_08(2019 Q1).csv", "test_2019_09(2019 Q1).csv", "test_2019_10(2019 Q1).csv", "test_2019_11(2019 Q1).csv", "test_2019_12(2019 Q1).csv" };
string QQ_test20[] = { "test_2013_Q1(2012 Q1).csv", "test_2013_Q2(2012 Q1).csv", "test_2013_Q3(2012 Q1).csv", "test_2013_Q4(2012 Q1).csv", "test_2014_Q1(2013 Q1).csv", "test_2014_Q2(2013 Q1).csv",
"test_2014_Q3(2013 Q1).csv", "test_2014_Q4(2013 Q1).csv", "test_2015_Q1(2014 Q1).csv", "test_2015_Q2(2014 Q1).csv", "test_2015_Q3(2014 Q1).csv", "test_2015_Q4(2014 Q1).csv", "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2015 Q1).csv", "test_2016_Q3(2015 Q1).csv", "test_2016_Q4(2015 Q1).csv", "test_2017_Q1(2016 Q1).csv", "test_2017_Q2(2016 Q1).csv", "test_2017_Q3(2016 Q1).csv", "test_2017_Q4(2016 Q1).csv", "test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2017 Q1).csv", "test_2018_Q3(2017 Q1).csv", "test_2018_Q4(2017 Q1).csv",
"test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2018 Q1).csv", "test_2019_Q3(2018 Q1).csv", "test_2019_Q4(2018 Q1).csv" };
string M2M_test20[] = { "test_2013_01(2012 Q1).csv","test_2013_02(2013 Q1).csv", "test_2013_03(2013 Q1).csv", "test_2013_04(2013 Q1).csv", "test_2013_05(2013 Q1).csv", "test_2013_06(2013 Q1).csv", "test_2013_07(2013 Q1).csv", "test_2013_08(2013 Q1).csv", "test_2013_09(2013 Q1).csv", "test_2013_10(2013 Q1).csv", "test_2013_11(2013 Q1).csv", "test_2013_12(2013 Q1).csv", "test_2014_01(2013 Q1).csv", "test_2014_02(2014 Q1).csv", "test_2014_03(2014 Q1).csv", "test_2014_04(2014 Q1).csv", "test_2014_05(2014 Q1).csv", "test_2014_06(2014 Q1).csv", "test_2014_07(2014 Q1).csv", "test_2014_08(2014 Q1).csv",
"test_2014_09(2014 Q1).csv", "test_2014_10(2014 Q1).csv", "test_2014_11(2014 Q1).csv", "test_2014_12(2014 Q1).csv", "test_2015_01(2014 Q1).csv", "test_2015_02(2015 Q1).csv", "test_2015_03(2015 Q1).csv", "test_2015_04(2015 Q1).csv", "test_2015_05(2015 Q1).csv", "test_2015_06(2015 Q1).csv", "test_2015_07(2015 Q1).csv", "test_2015_08(2015 Q1).csv", "test_2015_09(2015 Q1).csv", "test_2015_10(2015 Q1).csv", "test_2015_11(2015 Q1).csv", "test_2015_12(2015 Q1).csv", "test_2016_01(2015 Q1).csv", "test_2016_02(2016 Q1).csv", "test_2016_03(2016 Q1).csv",
"test_2016_04(2016 Q1).csv", "test_2016_05(2016 Q1).csv", "test_2016_06(2016 Q1).csv", "test_2016_07(2016 Q1).csv", "test_2016_08(2016 Q1).csv", "test_2016_09(2016 Q1).csv", "test_2016_10(2016 Q1).csv", "test_2016_11(2016 Q1).csv", "test_2016_12(2016 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2017 Q1).csv", "test_2017_03(2017 Q1).csv", "test_2017_04(2017 Q1).csv", "test_2017_05(2017 Q1).csv", "test_2017_06(2017 Q1).csv", "test_2017_07(2017 Q1).csv", "test_2017_08(2017 Q1).csv", "test_2017_09(2017 Q1).csv", "test_2017_10(2017 Q1).csv",
"test_2017_11(2017 Q1).csv", "test_2017_12(2017 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2018 Q1).csv", "test_2018_03(2018 Q1).csv", "test_2018_04(2018 Q1).csv", "test_2018_05(2018 Q1).csv", "test_2018_06(2018 Q1).csv", "test_2018_07(2018 Q1).csv", "test_2018_08(2018 Q1).csv", "test_2018_09(2018 Q1).csv", "test_2018_10(2018 Q1).csv", "test_2018_11(2018 Q1).csv", "test_2018_12(2018 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2019 Q1).csv", "test_2019_03(2019 Q1).csv", "test_2019_04(2019 Q1).csv", "test_2019_05(2019 Q1).csv",
"test_2019_06(2019 Q1).csv", "test_2019_07(2019 Q1).csv", "test_2019_08(2019 Q1).csv", "test_2019_09(2019 Q1).csv", "test_2019_10(2019 Q1).csv", "test_2019_11(2019 Q1).csv", "test_2019_12(2019 Q1).csv" };
string MM_test20[] = { "test_2013_01(2012 Q1).csv","test_2013_02(2012 Q1).csv", "test_2013_03(2012 Q1).csv", "test_2013_04(2012 Q1).csv", "test_2013_05(2012 Q1).csv", "test_2013_06(2012 Q1).csv", "test_2013_07(2012 Q1).csv", "test_2013_08(2012 Q1).csv", "test_2013_09(2012 Q1).csv", "test_2013_10(2012 Q1).csv", "test_2013_11(2012 Q1).csv", "test_2013_12(2012 Q1).csv", "test_2014_01(2013 Q1).csv", "test_2014_02(2013 Q1).csv", "test_2014_03(2013 Q1).csv", "test_2014_04(2013 Q1).csv", "test_2014_05(2013 Q1).csv", "test_2014_06(2013 Q1).csv", "test_2014_07(2013 Q1).csv", "test_2014_08(2013 Q1).csv",
"test_2014_09(2013 Q1).csv", "test_2014_10(2013 Q1).csv", "test_2014_11(2013 Q1).csv", "test_2014_12(2013 Q1).csv", "test_2015_01(2014 Q1).csv", "test_2015_02(2014 Q1).csv", "test_2015_03(2014 Q1).csv", "test_2015_04(2014 Q1).csv", "test_2015_05(2014 Q1).csv", "test_2015_06(2014 Q1).csv", "test_2015_07(2014 Q1).csv", "test_2015_08(2014 Q1).csv", "test_2015_09(2014 Q1).csv", "test_2015_10(2014 Q1).csv", "test_2015_11(2014 Q1).csv", "test_2015_12(2014 Q1).csv", "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv",
"test_2016_04(2015 Q1).csv", "test_2016_05(2015 Q1).csv", "test_2016_06(2015 Q1).csv", "test_2016_07(2015 Q1).csv", "test_2016_08(2015 Q1).csv", "test_2016_09(2015 Q1).csv", "test_2016_10(2015 Q1).csv", "test_2016_11(2015 Q1).csv", "test_2016_12(2015 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2016 Q1).csv", "test_2017_05(2016 Q1).csv", "test_2017_06(2016 Q1).csv", "test_2017_07(2016 Q1).csv", "test_2017_08(2016 Q1).csv", "test_2017_09(2016 Q1).csv", "test_2017_10(2016 Q1).csv",
"test_2017_11(2016 Q1).csv", "test_2017_12(2016 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2017 Q1).csv", "test_2018_05(2017 Q1).csv", "test_2018_06(2017 Q1).csv", "test_2018_07(2017 Q1).csv", "test_2018_08(2017 Q1).csv", "test_2018_09(2017 Q1).csv", "test_2018_10(2017 Q1).csv", "test_2018_11(2017 Q1).csv", "test_2018_12(2017 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2018 Q1).csv", "test_2019_05(2018 Q1).csv",
"test_2019_06(2018 Q1).csv", "test_2019_07(2018 Q1).csv", "test_2019_08(2018 Q1).csv", "test_2019_09(2018 Q1).csv", "test_2019_10(2018 Q1).csv", "test_2019_11(2018 Q1).csv", "test_2019_12(2018 Q1).csv" };
string H2Q_test20[] = { "test_2013_Q1(2012 Q1).csv", "test_2013_Q2(2012 Q1).csv", "test_2013_Q3(2013 Q1).csv", "test_2013_Q4(2013 Q1).csv", "test_2014_Q1(2013 Q1).csv", "test_2014_Q2(2013 Q1).csv","test_2014_Q3(2014 Q1).csv", "test_2014_Q4(2014 Q1).csv", "test_2015_Q1(2014 Q1).csv", "test_2015_Q2(2014 Q1).csv", "test_2015_Q3(2015 Q1).csv", "test_2015_Q4(2015 Q1).csv", "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2015 Q1).csv", "test_2016_Q3(2016 Q1).csv", "test_2016_Q4(2016 Q1).csv", "test_2017_Q1(2016 Q1).csv", "test_2017_Q2(2016 Q1).csv", "test_2017_Q3(2017 Q1).csv", "test_2017_Q4(2017 Q1).csv",
"test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2017 Q1).csv", "test_2018_Q3(2018 Q1).csv", "test_2018_Q4(2018 Q1).csv", "test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2018 Q1).csv", "test_2019_Q3(2019 Q1).csv", "test_2019_Q4(2019 Q1).csv" };
string H2M_test20[] = { "test_2013_01(2012 Q1).csv","test_2013_02(2012 Q1).csv", "test_2013_03(2012 Q1).csv", "test_2013_04(2012 Q1).csv", "test_2013_05(2012 Q1).csv", "test_2013_06(2012 Q1).csv", "test_2013_07(2013 Q1).csv", "test_2013_08(2013 Q1).csv", "test_2013_09(2013 Q1).csv", "test_2013_10(2013 Q1).csv", "test_2013_11(2013 Q1).csv", "test_2013_12(2013 Q1).csv", "test_2014_01(2013 Q1).csv", "test_2014_02(2013 Q1).csv", "test_2014_03(2013 Q1).csv", "test_2014_04(2013 Q1).csv", "test_2014_05(2013 Q1).csv", "test_2014_06(2013 Q1).csv", "test_2014_07(2014 Q1).csv", "test_2014_08(2014 Q1).csv",
"test_2014_09(2014 Q1).csv", "test_2014_10(2014 Q1).csv", "test_2014_11(2014 Q1).csv", "test_2014_12(2014 Q1).csv", "test_2015_01(2014 Q1).csv", "test_2015_02(2014 Q1).csv", "test_2015_03(2014 Q1).csv", "test_2015_04(2014 Q1).csv", "test_2015_05(2014 Q1).csv", "test_2015_06(2014 Q1).csv", "test_2015_07(2015 Q1).csv", "test_2015_08(2015 Q1).csv", "test_2015_09(2015 Q1).csv", "test_2015_10(2015 Q1).csv", "test_2015_11(2015 Q1).csv", "test_2015_12(2015 Q1).csv", "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv",
"test_2016_04(2015 Q1).csv", "test_2016_05(2015 Q1).csv", "test_2016_06(2015 Q1).csv", "test_2016_07(2016 Q1).csv", "test_2016_08(2016 Q1).csv", "test_2016_09(2016 Q1).csv", "test_2016_10(2016 Q1).csv", "test_2016_11(2016 Q1).csv", "test_2016_12(2016 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2016 Q1).csv", "test_2017_05(2016 Q1).csv", "test_2017_06(2016 Q1).csv", "test_2017_07(2017 Q1).csv", "test_2017_08(2017 Q1).csv", "test_2017_09(2017 Q1).csv", "test_2017_10(2017 Q1).csv",
"test_2017_11(2017 Q1).csv", "test_2017_12(2017 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2017 Q1).csv", "test_2018_05(2017 Q1).csv", "test_2018_06(2017 Q1).csv", "test_2018_07(2018 Q1).csv", "test_2018_08(2018 Q1).csv", "test_2018_09(2018 Q1).csv", "test_2018_10(2018 Q1).csv", "test_2018_11(2018 Q1).csv", "test_2018_12(2018 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2018 Q1).csv", "test_2019_05(2018 Q1).csv",
"test_2019_06(2018 Q1).csv", "test_2019_07(2019 Q1).csv", "test_2019_08(2019 Q1).csv", "test_2019_09(2019 Q1).csv", "test_2019_10(2019 Q1).csv", "test_2019_11(2019 Q1).csv", "test_2019_12(2019 Q1).csv" };
string HH_test20[] = { "test_2013_Q1-Q2(2012 Q1).csv", "test_2013_Q3-Q4(2012 Q1).csv", "test_2014_Q1-Q2(2013 Q1).csv", "test_2014_Q3-Q4(2013 Q1).csv", "test_2015_Q1-Q2(2014 Q1).csv", "test_2015_Q3-Q4(2014 Q1).csv", "test_2016_Q1-Q2(2015 Q1).csv", "test_2016_Q3-Q4(2015 Q1).csv", "test_2017_Q1-Q2(2016 Q1).csv", "test_2017_Q3-Q4(2016 Q1).csv", "test_2018_Q1-Q2(2017 Q1).csv", "test_2018_Q3-Q4(2017 Q1).csv", "test_2019_Q1-Q2(2018 Q1).csv","test_2019_Q3-Q4(2018 Q1).csv" };
string H2H_test20[] = { "test_2013_Q1-Q2(2012 Q1).csv", "test_2013_Q3-Q4(2013 Q1).csv", "test_2014_Q1-Q2(2013 Q1).csv", "test_2014_Q3-Q4(2014 Q1).csv", "test_2015_Q1-Q2(2014 Q1).csv", "test_2015_Q3-Q4(2015 Q1).csv", "test_2016_Q1-Q2(2015 Q1).csv","test_2016_Q3-Q4(2016 Q1).csv", "test_2017_Q1-Q2(2016 Q1).csv", "test_2017_Q3-Q4(2017 Q1).csv", "test_2018_Q1-Q2(2017 Q1).csv", "test_2018_Q3-Q4(2018 Q1).csv", "test_2019_Q1-Q2(2018 Q1).csv", "test_2019_Q3-Q4(2019 Q1).csv" };
/*���ȫe20�j���մ�*/

string Y2Y_trainDJI[] = { "train_2009(2009 Q1).csv", "train_2010(2010 Q1).csv", "train_2011(2011 Q1).csv", "train_2012(2012 Q1).csv", "train_2013(2013 Q1).csv", "train_2014(2014 Q1).csv", "train_2015(2015 Q1).csv", "train_2016(2016 Q1).csv", "train_2017(2017 Q1).csv", "train_2018(2018 Q1).csv" };
string Y2Q_trainDJI[] = { "train_2009(2009 Q1).csv", "train_2009_Q2~2010_Q1(2009 Q1).csv", "train_2009_Q3~2010_Q2(2009 Q1).csv", "train_2009_Q4~2010_Q3(2009 Q1).csv", "train_2010(2010 Q1).csv", "train_2010_Q2~2011_Q1(2010 Q1).csv", "train_2010_Q3~2011_Q2(2010 Q1).csv", "train_2010_Q4~2011_Q3(2010 Q1).csv", "train_2011(2011 Q1).csv",
"train_2011_Q2~2012_Q1(2011 Q1).csv", "train_2011_Q3~2012_Q2(2011 Q1).csv", "train_2011_Q4~2012_Q3(2011 Q1).csv", "train_2012(2012 Q1).csv", "train_2012_Q2~2013_Q1(2012 Q1).csv", "train_2012_Q3~2013_Q2(2012 Q1).csv", "train_2012_Q4~2013_Q3(2012 Q1).csv", "train_2013(2013 Q1).csv", "train_2013_Q2~2014_Q1(2013 Q1).csv",
"train_2013_Q3~2014_Q2(2013 Q1).csv", "train_2013_Q4~2014_Q3(2013 Q1).csv", "train_2014(2014 Q1).csv", "train_2014_Q2~2015_Q1(2014 Q1).csv", "train_2014_Q3~2015_Q2(2014 Q1).csv", "train_2014_Q4~2015_Q3(2014 Q1).csv", "train_2015(2015 Q1).csv",
"train_2015_Q2~2016_Q1(2015 Q1).csv", "train_2015_Q3~2016_Q2(2015 Q1).csv", "train_2015_Q4~2016_Q3(2015 Q1).csv", "train_2016(2016 Q1).csv", "train_2016_Q2~2017_Q1(2016 Q1).csv", "train_2016_Q3~2017_Q2(2016 Q1).csv", "train_2016_Q4~2017_Q3(2016 Q1).csv",
"train_2017(2017 Q1).csv", "train_2017_Q2~2018_Q1(2017 Q1).csv", "train_2017_Q3~2018_Q2(2017 Q1).csv", "train_2017_Q4~2018_Q3(2017 Q1).csv", "train_2018(2018 Q1).csv", "train_2018_Q2~2019_Q1(2018 Q1).csv", "train_2018_Q3~2019_Q2(2018 Q1).csv", "train_2018_Q4~2019_Q3(2018 Q1).csv" };
string Y2M_trainDJI[] = { "train_2009(2009 Q1).csv", "train_2009_02~2010_01(2009 Q1).csv", "train_2009_03~2010_02(2009 Q1).csv", "train_2009_04~2010_03(2009 Q1).csv", "train_2009_05~2010_04(2009 Q1).csv", "train_2009_06~2010_05(2009 Q1).csv", "train_2009_07~2010_06(2009 Q1).csv", "train_2009_08~2010_07(2009 Q1).csv", "train_2009_09~2010_08(2009 Q1).csv", "train_2009_10~2010_09(2009 Q1).csv", "train_2009_11~2010_10(2009 Q1).csv", "train_2009_12~2010_11(2009 Q1).csv",
"train_2010(2010 Q1).csv", "train_2010_02~2011_01(2010 Q1).csv", "train_2010_03~2011_02(2010 Q1).csv", "train_2010_04~2011_03(2010 Q1).csv", "train_2010_05~2011_04(2010 Q1).csv", "train_2010_06~2011_05(2010 Q1).csv", "train_2010_07~2011_06(2010 Q1).csv", "train_2010_08~2011_07(2010 Q1).csv", "train_2010_09~2011_08(2010 Q1).csv", "train_2010_10~2011_09(2010 Q1).csv", "train_2010_11~2011_10(2010 Q1).csv", "train_2010_12~2011_11(2010 Q1).csv",
"train_2011(2011 Q1).csv", "train_2011_02~2012_01(2011 Q1).csv", "train_2011_03~2012_02(2011 Q1).csv", "train_2011_04~2012_03(2011 Q1).csv", "train_2011_05~2012_04(2011 Q1).csv", "train_2011_06~2012_05(2011 Q1).csv", "train_2011_07~2012_06(2011 Q1).csv", "train_2011_08~2012_07(2011 Q1).csv", "train_2011_09~2012_08(2011 Q1).csv", "train_2011_10~2012_09(2011 Q1).csv", "train_2011_11~2012_10(2011 Q1).csv", "train_2011_12~2012_11(2011 Q1).csv","train_2012(2012 Q1).csv", "train_2012_02~2013_01(2012 Q1).csv", "train_2012_03~2013_02(2012 Q1).csv", "train_2012_04~2013_03(2012 Q1).csv", "train_2012_05~2013_04(2012 Q1).csv", "train_2012_06~2013_05(2012 Q1).csv", "train_2012_07~2013_06(2012 Q1).csv", "train_2012_08~2013_07(2012 Q1).csv", "train_2012_09~2013_08(2012 Q1).csv", "train_2012_10~2013_09(2012 Q1).csv", "train_2012_11~2013_10(2012 Q1).csv", "train_2012_12~2013_11(2012 Q1).csv",
"train_2013(2013 Q1).csv", "train_2013_02~2014_01(2013 Q1).csv", "train_2013_03~2014_02(2013 Q1).csv", "train_2013_04~2014_03(2013 Q1).csv", "train_2013_05~2014_04(2013 Q1).csv", "train_2013_06~2014_05(2013 Q1).csv", "train_2013_07~2014_06(2013 Q1).csv", "train_2013_08~2014_07(2013 Q1).csv", "train_2013_09~2014_08(2013 Q1).csv", "train_2013_10~2014_09(2013 Q1).csv", "train_2013_11~2014_10(2013 Q1).csv", "train_2013_12~2014_11(2013 Q1).csv",
"train_2014(2014 Q1).csv", "train_2014_02~2015_01(2014 Q1).csv", "train_2014_03~2015_02(2014 Q1).csv", "train_2014_04~2015_03(2014 Q1).csv", "train_2014_05~2015_04(2014 Q1).csv", "train_2014_06~2015_05(2014 Q1).csv", "train_2014_07~2015_06(2014 Q1).csv", "train_2014_08~2015_07(2014 Q1).csv", "train_2014_09~2015_08(2014 Q1).csv", "train_2014_10~2015_09(2014 Q1).csv", "train_2014_11~2015_10(2014 Q1).csv", "train_2014_12~2015_11(2014 Q1).csv",
"train_2015(2015 Q1).csv", "train_2015_02~2016_01(2015 Q1).csv", "train_2015_03~2016_02(2015 Q1).csv", "train_2015_04~2016_03(2015 Q1).csv", "train_2015_05~2016_04(2015 Q1).csv", "train_2015_06~2016_05(2015 Q1).csv", "train_2015_07~2016_06(2015 Q1).csv", "train_2015_08~2016_07(2015 Q1).csv", "train_2015_09~2016_08(2015 Q1).csv", "train_2015_10~2016_09(2015 Q1).csv", "train_2015_11~2016_10(2015 Q1).csv", "train_2015_12~2016_11(2015 Q1).csv",
"train_2016(2016 Q1).csv", "train_2016_02~2017_01(2016 Q1).csv", "train_2016_03~2017_02(2016 Q1).csv", "train_2016_04~2017_03(2016 Q1).csv", "train_2016_05~2017_04(2016 Q1).csv", "train_2016_06~2017_05(2016 Q1).csv", "train_2016_07~2017_06(2016 Q1).csv", "train_2016_08~2017_07(2016 Q1).csv", "train_2016_09~2017_08(2016 Q1).csv", "train_2016_10~2017_09(2016 Q1).csv", "train_2016_11~2017_10(2016 Q1).csv", "train_2016_12~2017_11(2016 Q1).csv",
"train_2017(2017 Q1).csv", "train_2017_02~2018_01(2017 Q1).csv", "train_2017_03~2018_02(2017 Q1).csv", "train_2017_04~2018_03(2017 Q1).csv", "train_2017_05~2018_04(2017 Q1).csv", "train_2017_06~2018_05(2017 Q1).csv", "train_2017_07~2018_06(2017 Q1).csv", "train_2017_08~2018_07(2017 Q1).csv", "train_2017_09~2018_08(2017 Q1).csv", "train_2017_10~2018_09(2017 Q1).csv", "train_2017_11~2018_10(2017 Q1).csv", "train_2017_12~2018_11(2017 Q1).csv",
"train_2018(2018 Q1).csv", "train_2018_02~2019_01(2018 Q1).csv", "train_2018_03~2019_02(2018 Q1).csv", "train_2018_04~2019_03(2018 Q1).csv", "train_2018_05~2019_04(2018 Q1).csv", "train_2018_06~2019_05(2018 Q1).csv", "train_2018_07~2019_06(2018 Q1).csv", "train_2018_08~2019_07(2018 Q1).csv", "train_2018_09~2019_08(2018 Q1).csv", "train_2018_10~2019_09(2018 Q1).csv", "train_2018_11~2019_10(2018 Q1).csv", "train_2018_12~2019_11(2018 Q1).csv" };
string Y2H_trainDJI[] = { "train_2009(2009 Q1).csv", "train_2009_Q3~2010_Q2(2009 Q1).csv", "train_2010(2010 Q1).csv", "train_2010_Q3~2011_Q2(2010 Q1).csv", "train_2011(2011 Q1).csv", "train_2011_Q3~2012_Q2(2011 Q1).csv", "train_2012(2012 Q1).csv", "train_2012_Q3~2013_Q2(2012 Q1).csv", "train_2013(2013 Q1).csv", "train_2013_Q3~2014_Q2(2013 Q1).csv", "train_2014(2014 Q1).csv", "train_2014_Q3~2015_Q2(2014 Q1).csv", "train_2015(2015 Q1).csv", "train_2015_Q3~2016_Q2(2015 Q1).csv",
"train_2016(2016 Q1).csv", "train_2016_Q3~2017_Q2(2016 Q1).csv", "train_2017(2017 Q1).csv", "train_2017_Q3~2018_Q2(2017 Q1).csv", "train_2018(2018 Q1).csv", "train_2018_Q3~2019_Q2(2018 Q1).csv" };
string Q2Q_trainDJI[] = { "train_2009_Q4(2009 Q1).csv", "train_2010_Q1(2010 Q1).csv", "train_2010_Q2(2010 Q1).csv", "train_2010_Q3(2010 Q1).csv", "train_2010_Q4(2010 Q1).csv", "train_2011_Q1(2011 Q1).csv", "train_2011_Q2(2011 Q1).csv", "train_2011_Q3(2011 Q1).csv", "train_2011_Q4(2011 Q1).csv", "train_2012_Q1(2012 Q1).csv", "train_2012_Q2(2012 Q1).csv", "train_2012_Q3(2012 Q1).csv", "train_2012_Q4(2012 Q1).csv", "train_2013_Q1(2013 Q1).csv", "train_2013_Q2(2013 Q1).csv", "train_2013_Q3(2013 Q1).csv", "train_2013_Q4(2013 Q1).csv", "train_2014_Q1(2014 Q1).csv", "train_2014_Q2(2014 Q1).csv", "train_2014_Q3(2014 Q1).csv", "train_2014_Q4(2014 Q1).csv", "train_2015_Q1(2015 Q1).csv", "train_2015_Q2(2015 Q1).csv", "train_2015_Q3(2015 Q1).csv", "train_2015_Q4(2015 Q1).csv", "train_2016_Q1(2016 Q1).csv", "train_2016_Q2(2016 Q1).csv",
"train_2016_Q3(2016 Q1).csv", "train_2016_Q4(2016 Q1).csv", "train_2017_Q1(2017 Q1).csv", "train_2017_Q2(2017 Q1).csv", "train_2017_Q3(2017 Q1).csv", "train_2017_Q4(2017 Q1).csv", "train_2018_Q1(2018 Q1).csv", "train_2018_Q2(2018 Q1).csv", "train_2018_Q3(2018 Q1).csv", "train_2018_Q4(2018 Q1).csv", "train_2019_Q1(2019 Q1).csv", "train_2019_Q2(2019 Q1).csv", "train_2019_Q3(2019 Q1).csv" };
string Q2M_trainDJI[] = { "train_2009_10-12(2009 Q1).csv", "train_2009_11~2010_01(2009 Q1).csv", "train_2009_12~2010_02(2009 Q1).csv", "train_2010_01-03(2010 Q1).csv", "train_2010_02-04(2010 Q1).csv", "train_2010_03-05(2010 Q1).csv", "train_2010_04-06(2010 Q1).csv", "train_2010_05-07(2010 Q1).csv", "train_2010_06-08(2010 Q1).csv", "train_2010_07-09(2010 Q1).csv", "train_2010_08-10(2010 Q1).csv", "train_2010_09-11(2010 Q1).csv", "train_2010_10-12(2010 Q1).csv", "train_2010_11~2011_01(2010 Q1).csv",
"train_2010_12~2011_02(2010 Q1).csv", "train_2011_01-03(2011 Q1).csv", "train_2011_02-04(2011 Q1).csv", "train_2011_03-05(2011 Q1).csv", "train_2011_04-06(2011 Q1).csv", "train_2011_05-07(2011 Q1).csv", "train_2011_06-08(2011 Q1).csv", "train_2011_07-09(2011 Q1).csv", "train_2011_08-10(2011 Q1).csv", "train_2011_09-11(2011 Q1).csv", "train_2011_10-12(2011 Q1).csv", "train_2011_11~2012_01(2011 Q1).csv", "train_2011_12~2012_02(2011 Q1).csv", "train_2012_01-03(2012 Q1).csv",
"train_2012_02-04(2012 Q1).csv", "train_2012_03-05(2012 Q1).csv", "train_2012_04-06(2012 Q1).csv", "train_2012_05-07(2012 Q1).csv", "train_2012_06-08(2012 Q1).csv", "train_2012_07-09(2012 Q1).csv", "train_2012_08-10(2012 Q1).csv", "train_2012_09-11(2012 Q1).csv", "train_2012_10-12(2012 Q1).csv", "train_2012_11~2013_01(2012 Q1).csv", "train_2012_12~2013_02(2012 Q1).csv", "train_2013_01-03(2013 Q1).csv", "train_2013_02-04(2013 Q1).csv", "train_2013_03-05(2013 Q1).csv",
"train_2013_04-06(2013 Q1).csv", "train_2013_05-07(2013 Q1).csv", "train_2013_06-08(2013 Q1).csv", "train_2013_07-09(2013 Q1).csv", "train_2013_08-10(2013 Q1).csv", "train_2013_09-11(2013 Q1).csv", "train_2013_10-12(2013 Q1).csv", "train_2013_11~2014_01(2013 Q1).csv", "train_2013_12~2014_02(2013 Q1).csv", "train_2014_01-03(2014 Q1).csv", "train_2014_02-04(2014 Q1).csv", "train_2014_03-05(2014 Q1).csv", "train_2014_04-06(2014 Q1).csv", "train_2014_05-07(2014 Q1).csv",
"train_2014_06-08(2014 Q1).csv", "train_2014_07-09(2014 Q1).csv", "train_2014_08-10(2014 Q1).csv", "train_2014_09-11(2014 Q1).csv", "train_2014_10-12(2014 Q1).csv", "train_2014_11~2015_01(2014 Q1).csv", "train_2014_12~2015_02(2014 Q1).csv", "train_2015_01-03(2015 Q1).csv", "train_2015_02-04(2015 Q1).csv", "train_2015_03-05(2015 Q1).csv", "train_2015_04-06(2015 Q1).csv", "train_2015_05-07(2015 Q1).csv", "train_2015_06-08(2015 Q1).csv", "train_2015_07-09(2015 Q1).csv",
"train_2015_08-10(2015 Q1).csv", "train_2015_09-11(2015 Q1).csv", "train_2015_10-12(2015 Q1).csv", "train_2015_11~2016_01(2015 Q1).csv", "train_2015_12~2016_02(2015 Q1).csv", "train_2016_01-03(2016 Q1).csv", "train_2016_02-04(2016 Q1).csv", "train_2016_03-05(2016 Q1).csv", "train_2016_04-06(2016 Q1).csv", "train_2016_05-07(2016 Q1).csv", "train_2016_06-08(2016 Q1).csv", "train_2016_07-09(2016 Q1).csv", "train_2016_08-10(2016 Q1).csv", "train_2016_09-11(2016 Q1).csv",
"train_2016_10-12(2016 Q1).csv", "train_2016_11~2017_01(2016 Q1).csv", "train_2016_12~2017_02(2016 Q1).csv", "train_2017_01-03(2017 Q1).csv", "train_2017_02-04(2017 Q1).csv", "train_2017_03-05(2017 Q1).csv", "train_2017_04-06(2017 Q1).csv", "train_2017_05-07(2017 Q1).csv", "train_2017_06-08(2017 Q1).csv", "train_2017_07-09(2017 Q1).csv", "train_2017_08-10(2017 Q1).csv", "train_2017_09-11(2017 Q1).csv", "train_2017_10-12(2017 Q1).csv", "train_2017_11~2018_01(2017 Q1).csv",
"train_2017_12~2018_02(2017 Q1).csv", "train_2018_01-03(2018 Q1).csv", "train_2018_02-04(2018 Q1).csv", "train_2018_03-05(2018 Q1).csv", "train_2018_04-06(2018 Q1).csv", "train_2018_05-07(2018 Q1).csv", "train_2018_06-08(2018 Q1).csv", "train_2018_07-09(2018 Q1).csv", "train_2018_08-10(2018 Q1).csv", "train_2018_09-11(2018 Q1).csv", "train_2018_10-12(2018 Q1).csv", "train_2018_11~2019_01(2018 Q1).csv", "train_2018_12~2019_02(2018 Q1).csv", "train_2019_01-03(2019 Q1).csv", "train_2019_02-04(2019 Q1).csv",
"train_2019_03-05(2019 Q1).csv", "train_2019_04-06(2019 Q1).csv", "train_2019_05-07(2019 Q1).csv", "train_2019_06-08(2019 Q1).csv", "train_2019_07-09(2019 Q1).csv", "train_2019_08-10(2019 Q1).csv", "train_2019_09-11(2019 Q1).csv" };
string QQ_trainDJI[] = { "train_2009_Q1(2009 Q1).csv", "train_2009_Q2(2009 Q1).csv", "train_2009_Q3(2009 Q1).csv", "train_2009_Q4(2009 Q1).csv", "train_2010_Q1(2010 Q1).csv", "train_2010_Q2(2010 Q1).csv", "train_2010_Q3(2010 Q1).csv", "train_2010_Q4(2010 Q1).csv", "train_2011_Q1(2011 Q1).csv", "train_2011_Q2(2011 Q1).csv", "train_2011_Q3(2011 Q1).csv", "train_2011_Q4(2011 Q1).csv", "train_2012_Q1(2012 Q1).csv", "train_2012_Q2(2012 Q1).csv", "train_2012_Q3(2012 Q1).csv", "train_2012_Q4(2012 Q1).csv", "train_2013_Q1(2013 Q1).csv", "train_2013_Q2(2013 Q1).csv", "train_2013_Q3(2013 Q1).csv", "train_2013_Q4(2013 Q1).csv", "train_2014_Q1(2014 Q1).csv", "train_2014_Q2(2014 Q1).csv", "train_2014_Q3(2014 Q1).csv", "train_2014_Q4(2014 Q1).csv", "train_2015_Q1(2015 Q1).csv", "train_2015_Q2(2015 Q1).csv", "train_2015_Q3(2015 Q1).csv", "train_2015_Q4(2015 Q1).csv",
"train_2016_Q1(2016 Q1).csv", "train_2016_Q2(2016 Q1).csv", "train_2016_Q3(2016 Q1).csv", "train_2016_Q4(2016 Q1).csv", "train_2017_Q1(2017 Q1).csv", "train_2017_Q2(2017 Q1).csv", "train_2017_Q3(2017 Q1).csv", "train_2017_Q4(2017 Q1).csv", "train_2018_Q1(2018 Q1).csv", "train_2018_Q2(2018 Q1).csv", "train_2018_Q3(2018 Q1).csv", "train_2018_Q4(2018 Q1).csv" };
string M2M_trainDJI[] = { "train_2009_12(2009 Q1).csv", "train_2010_01(2010 Q1).csv", "train_2010_02(2010 Q1).csv", "train_2010_03(2010 Q1).csv", "train_2010_04(2010 Q1).csv", "train_2010_05(2010 Q1).csv", "train_2010_06(2010 Q1).csv", "train_2010_07(2010 Q1).csv", "train_2010_08(2010 Q1).csv", "train_2010_09(2010 Q1).csv", "train_2010_10(2010 Q1).csv", "train_2010_11(2010 Q1).csv", "train_2010_12(2010 Q1).csv", "train_2011_01(2011 Q1).csv",
"train_2011_02(2011 Q1).csv", "train_2011_03(2011 Q1).csv", "train_2011_04(2011 Q1).csv", "train_2011_05(2011 Q1).csv", "train_2011_06(2011 Q1).csv", "train_2011_07(2011 Q1).csv", "train_2011_08(2011 Q1).csv", "train_2011_09(2011 Q1).csv", "train_2011_10(2011 Q1).csv", "train_2011_11(2011 Q1).csv", "train_2011_12(2011 Q1).csv", "train_2012_01(2012 Q1).csv", "train_2012_02(2012 Q1).csv", "train_2012_03(2012 Q1).csv",
"train_2012_04(2012 Q1).csv", "train_2012_05(2012 Q1).csv", "train_2012_06(2012 Q1).csv", "train_2012_07(2012 Q1).csv", "train_2012_08(2012 Q1).csv", "train_2012_09(2012 Q1).csv", "train_2012_10(2012 Q1).csv", "train_2012_11(2012 Q1).csv", "train_2012_12(2012 Q1).csv", "train_2013_01(2013 Q1).csv", "train_2013_02(2013 Q1).csv", "train_2013_03(2013 Q1).csv", "train_2013_04(2013 Q1).csv", "train_2013_05(2013 Q1).csv",
"train_2013_06(2013 Q1).csv", "train_2013_07(2013 Q1).csv", "train_2013_08(2013 Q1).csv", "train_2013_09(2013 Q1).csv", "train_2013_10(2013 Q1).csv", "train_2013_11(2013 Q1).csv", "train_2013_12(2013 Q1).csv", "train_2014_01(2014 Q1).csv", "train_2014_02(2014 Q1).csv", "train_2014_03(2014 Q1).csv", "train_2014_04(2014 Q1).csv", "train_2014_05(2014 Q1).csv", "train_2014_06(2014 Q1).csv", "train_2014_07(2014 Q1).csv",
"train_2014_08(2014 Q1).csv", "train_2014_09(2014 Q1).csv", "train_2014_10(2014 Q1).csv", "train_2014_11(2014 Q1).csv", "train_2014_12(2014 Q1).csv", "train_2015_01(2015 Q1).csv", "train_2015_02(2015 Q1).csv", "train_2015_03(2015 Q1).csv", "train_2015_04(2015 Q1).csv", "train_2015_05(2015 Q1).csv", "train_2015_06(2015 Q1).csv", "train_2015_07(2015 Q1).csv", "train_2015_08(2015 Q1).csv", "train_2015_09(2015 Q1).csv",
"train_2015_10(2015 Q1).csv", "train_2015_11(2015 Q1).csv", "train_2015_12(2015 Q1).csv", "train_2016_01(2016 Q1).csv", "train_2016_02(2016 Q1).csv", "train_2016_03(2016 Q1).csv", "train_2016_04(2016 Q1).csv", "train_2016_05(2016 Q1).csv", "train_2016_06(2016 Q1).csv", "train_2016_07(2016 Q1).csv", "train_2016_08(2016 Q1).csv", "train_2016_09(2016 Q1).csv", "train_2016_10(2016 Q1).csv", "train_2016_11(2016 Q1).csv",
"train_2016_12(2016 Q1).csv", "train_2017_01(2017 Q1).csv", "train_2017_02(2017 Q1).csv", "train_2017_03(2017 Q1).csv", "train_2017_04(2017 Q1).csv", "train_2017_05(2017 Q1).csv", "train_2017_06(2017 Q1).csv", "train_2017_07(2017 Q1).csv", "train_2017_08(2017 Q1).csv", "train_2017_09(2017 Q1).csv", "train_2017_10(2017 Q1).csv", "train_2017_11(2017 Q1).csv", "train_2017_12(2017 Q1).csv", "train_2018_01(2018 Q1).csv",
"train_2018_02(2018 Q1).csv", "train_2018_03(2018 Q1).csv", "train_2018_04(2018 Q1).csv", "train_2018_05(2018 Q1).csv", "train_2018_06(2018 Q1).csv", "train_2018_07(2018 Q1).csv", "train_2018_08(2018 Q1).csv", "train_2018_09(2018 Q1).csv", "train_2018_10(2018 Q1).csv", "train_2018_11(2018 Q1).csv", "train_2018_12(2018 Q1).csv", "train_2019_01(2019 Q1).csv", "train_2019_02(2019 Q1).csv", "train_2019_03(2019 Q1).csv",
"train_2019_04(2019 Q1).csv", "train_2019_05(2019 Q1).csv", "train_2019_06(2019 Q1).csv", "train_2019_07(2019 Q1).csv", "train_2019_08(2019 Q1).csv", "train_2019_09(2019 Q1).csv", "train_2019_10(2019 Q1).csv", "train_2019_11(2019 Q1).csv" };
string MM_trainDJI[] = { "train_2009_01(2009 Q1).csv", "train_2009_02(2009 Q1).csv", "train_2009_03(2009 Q1).csv", "train_2009_04(2009 Q1).csv", "train_2009_05(2009 Q1).csv", "train_2009_06(2009 Q1).csv", "train_2009_07(2009 Q1).csv", "train_2009_08(2009 Q1).csv", "train_2009_09(2009 Q1).csv", "train_2009_10(2009 Q1).csv", "train_2009_11(2009 Q1).csv", "train_2009_12(2009 Q1).csv", "train_2010_01(2010 Q1).csv", "train_2010_02(2010 Q1).csv", "train_2010_03(2010 Q1).csv", "train_2010_04(2010 Q1).csv", "train_2010_05(2010 Q1).csv",
"train_2010_06(2010 Q1).csv", "train_2010_07(2010 Q1).csv", "train_2010_08(2010 Q1).csv", "train_2010_09(2010 Q1).csv", "train_2010_10(2010 Q1).csv", "train_2010_11(2010 Q1).csv", "train_2010_12(2010 Q1).csv", "train_2011_01(2011 Q1).csv", "train_2011_02(2011 Q1).csv", "train_2011_03(2011 Q1).csv", "train_2011_04(2011 Q1).csv", "train_2011_05(2011 Q1).csv", "train_2011_06(2011 Q1).csv", "train_2011_07(2011 Q1).csv", "train_2011_08(2011 Q1).csv", "train_2011_09(2011 Q1).csv", "train_2011_10(2011 Q1).csv",
"train_2011_11(2011 Q1).csv", "train_2011_12(2011 Q1).csv", "train_2012_01(2012 Q1).csv", "train_2012_02(2012 Q1).csv", "train_2012_03(2012 Q1).csv", "train_2012_04(2012 Q1).csv", "train_2012_05(2012 Q1).csv", "train_2012_06(2012 Q1).csv", "train_2012_07(2012 Q1).csv", "train_2012_08(2012 Q1).csv", "train_2012_09(2012 Q1).csv", "train_2012_10(2012 Q1).csv", "train_2012_11(2012 Q1).csv", "train_2012_12(2012 Q1).csv", "train_2013_01(2013 Q1).csv", "train_2013_02(2013 Q1).csv", "train_2013_03(2013 Q1).csv",
"train_2013_04(2013 Q1).csv", "train_2013_05(2013 Q1).csv", "train_2013_06(2013 Q1).csv", "train_2013_07(2013 Q1).csv", "train_2013_08(2013 Q1).csv", "train_2013_09(2013 Q1).csv", "train_2013_10(2013 Q1).csv", "train_2013_11(2013 Q1).csv", "train_2013_12(2013 Q1).csv", "train_2014_01(2014 Q1).csv", "train_2014_02(2014 Q1).csv", "train_2014_03(2014 Q1).csv", "train_2014_04(2014 Q1).csv", "train_2014_05(2014 Q1).csv", "train_2014_06(2014 Q1).csv", "train_2014_07(2014 Q1).csv", "train_2014_08(2014 Q1).csv",
"train_2014_09(2014 Q1).csv", "train_2014_10(2014 Q1).csv", "train_2014_11(2014 Q1).csv", "train_2014_12(2014 Q1).csv", "train_2015_01(2015 Q1).csv", "train_2015_02(2015 Q1).csv", "train_2015_03(2015 Q1).csv", "train_2015_04(2015 Q1).csv", "train_2015_05(2015 Q1).csv", "train_2015_06(2015 Q1).csv", "train_2015_07(2015 Q1).csv", "train_2015_08(2015 Q1).csv", "train_2015_09(2015 Q1).csv", "train_2015_10(2015 Q1).csv", "train_2015_11(2015 Q1).csv", "train_2015_12(2015 Q1).csv", "train_2016_01(2016 Q1).csv",
"train_2016_02(2016 Q1).csv", "train_2016_03(2016 Q1).csv", "train_2016_04(2016 Q1).csv", "train_2016_05(2016 Q1).csv", "train_2016_06(2016 Q1).csv", "train_2016_07(2016 Q1).csv", "train_2016_08(2016 Q1).csv", "train_2016_09(2016 Q1).csv", "train_2016_10(2016 Q1).csv", "train_2016_11(2016 Q1).csv", "train_2016_12(2016 Q1).csv", "train_2017_01(2017 Q1).csv", "train_2017_02(2017 Q1).csv", "train_2017_03(2017 Q1).csv", "train_2017_04(2017 Q1).csv", "train_2017_05(2017 Q1).csv", "train_2017_06(2017 Q1).csv",
"train_2017_07(2017 Q1).csv", "train_2017_08(2017 Q1).csv", "train_2017_09(2017 Q1).csv", "train_2017_10(2017 Q1).csv", "train_2017_11(2017 Q1).csv", "train_2017_12(2017 Q1).csv", "train_2018_01(2018 Q1).csv", "train_2018_02(2018 Q1).csv", "train_2018_03(2018 Q1).csv", "train_2018_04(2018 Q1).csv", "train_2018_05(2018 Q1).csv", "train_2018_06(2018 Q1).csv", "train_2018_07(2018 Q1).csv", "train_2018_08(2018 Q1).csv", "train_2018_09(2018 Q1).csv", "train_2018_10(2018 Q1).csv", "train_2018_11(2018 Q1).csv",
"train_2018_12(2018 Q1).csv" };
string H2Q_trainDJI[] = { "train_2009_Q3-Q4(2009 Q1).csv", "train_2009_Q4~2010_Q1(2009 Q1).csv", "train_2010_Q1-Q2(2010 Q1).csv", "train_2010_Q2-Q3(2010 Q1).csv", "train_2010_Q3-Q4(2010 Q1).csv", "train_2010_Q4~2011_Q1(2010 Q1).csv", "train_2011_Q1-Q2(2011 Q1).csv", "train_2011_Q2-Q3(2011 Q1).csv", "train_2011_Q3-Q4(2011 Q1).csv", "train_2011_Q4~2012_Q1(2011 Q1).csv", "train_2012_Q1-Q2(2012 Q1).csv", "train_2012_Q2-Q3(2012 Q1).csv", "train_2012_Q3-Q4(2012 Q1).csv", "train_2012_Q4~2013_Q1(2012 Q1).csv",
"train_2013_Q1-Q2(2013 Q1).csv", "train_2013_Q2-Q3(2013 Q1).csv", "train_2013_Q3-Q4(2013 Q1).csv", "train_2013_Q4~2014_Q1(2013 Q1).csv", "train_2014_Q1-Q2(2014 Q1).csv", "train_2014_Q2-Q3(2014 Q1).csv", "train_2014_Q3-Q4(2014 Q1).csv", "train_2014_Q4~2015_Q1(2014 Q1).csv", "train_2015_Q1-Q2(2015 Q1).csv", "train_2015_Q2-Q3(2015 Q1).csv", "train_2015_Q3-Q4(2015 Q1).csv", "train_2015_Q4~2016_Q1(2015 Q1).csv", "train_2016_Q1-Q2(2016 Q1).csv", "train_2016_Q2-Q3(2016 Q1).csv",
"train_2016_Q3-Q4(2016 Q1).csv", "train_2016_Q4~2017_Q1(2016 Q1).csv", "train_2017_Q1-Q2(2017 Q1).csv", "train_2017_Q2-Q3(2017 Q1).csv", "train_2017_Q3-Q4(2017 Q1).csv", "train_2017_Q4~2018_Q1(2017 Q1).csv", "train_2018_Q1-Q2(2018 Q1).csv", "train_2018_Q2-Q3(2018 Q1).csv", "train_2018_Q3-Q4(2018 Q1).csv", "train_2018_Q4~2019_Q1(2018 Q1).csv", "train_2019_Q1-Q2(2019 Q1).csv", "train_2019_Q2-Q3(2019 Q1).csv" };
string H2M_trainDJI[] = { "train_2009_07-12(2009 Q1).csv", "train_2009_08~2010_01(2009 Q1).csv", "train_2009_09~2010_02(2009 Q1).csv", "train_2009_10~2010_03(2009 Q1).csv", "train_2009_11~2010_04(2009 Q1).csv", "train_2009_12~2010_05(2009 Q1).csv", "train_2010_01-06(2010 Q1).csv", "train_2010_02-07(2010 Q1).csv", "train_2010_03-08(2010 Q1).csv", "train_2010_04-09(2010 Q1).csv", "train_2010_05-10(2010 Q1).csv", "train_2010_06-11(2010 Q1).csv", "train_2010_07-12(2010 Q1).csv",
"train_2010_08~2011_01(2010 Q1).csv", "train_2010_09~2011_02(2010 Q1).csv", "train_2010_10~2011_03(2010 Q1).csv", "train_2010_11~2011_04(2010 Q1).csv", "train_2010_12~2011_05(2010 Q1).csv", "train_2011_01-06(2011 Q1).csv", "train_2011_02-07(2011 Q1).csv", "train_2011_03-08(2011 Q1).csv", "train_2011_04-09(2011 Q1).csv", "train_2011_05-10(2011 Q1).csv", "train_2011_06-11(2011 Q1).csv", "train_2011_07-12(2011 Q1).csv", "train_2011_08~2012_01(2011 Q1).csv",
"train_2011_09~2012_02(2011 Q1).csv", "train_2011_10~2012_03(2011 Q1).csv", "train_2011_11~2012_04(2011 Q1).csv", "train_2011_12~2012_05(2011 Q1).csv", "train_2012_01-06(2012 Q1).csv", "train_2012_02-07(2012 Q1).csv", "train_2012_03-08(2012 Q1).csv", "train_2012_04-09(2012 Q1).csv", "train_2012_05-10(2012 Q1).csv", "train_2012_06-11(2012 Q1).csv", "train_2012_07-12(2012 Q1).csv", "train_2012_08~2013_01(2012 Q1).csv", "train_2012_09~2013_02(2012 Q1).csv",
"train_2012_10~2013_03(2012 Q1).csv", "train_2012_11~2013_04(2012 Q1).csv", "train_2012_12~2013_05(2012 Q1).csv", "train_2013_01-06(2013 Q1).csv", "train_2013_02-07(2013 Q1).csv", "train_2013_03-08(2013 Q1).csv", "train_2013_04-09(2013 Q1).csv", "train_2013_05-10(2013 Q1).csv", "train_2013_06-11(2013 Q1).csv", "train_2013_07-12(2013 Q1).csv", "train_2013_08~2014_01(2013 Q1).csv", "train_2013_09~2014_02(2013 Q1).csv",
"train_2013_10~2014_03(2013 Q1).csv", "train_2013_11~2014_04(2013 Q1).csv", "train_2013_12~2014_05(2013 Q1).csv", "train_2014_01-06(2014 Q1).csv", "train_2014_02-07(2014 Q1).csv", "train_2014_03-08(2014 Q1).csv", "train_2014_04-09(2014 Q1).csv", "train_2014_05-10(2014 Q1).csv", "train_2014_06-11(2014 Q1).csv", "train_2014_07-12(2014 Q1).csv", "train_2014_08~2015_01(2014 Q1).csv", "train_2014_09~2015_02(2014 Q1).csv", "train_2014_10~2015_03(2014 Q1).csv",
"train_2014_11~2015_04(2014 Q1).csv", "train_2014_12~2015_05(2014 Q1).csv", "train_2015_01-06(2015 Q1).csv", "train_2015_02-07(2015 Q1).csv", "train_2015_03-08(2015 Q1).csv", "train_2015_04-09(2015 Q1).csv", "train_2015_05-10(2015 Q1).csv", "train_2015_06-11(2015 Q1).csv", "train_2015_07-12(2015 Q1).csv", "train_2015_08~2016_01(2015 Q1).csv", "train_2015_09~2016_02(2015 Q1).csv", "train_2015_10~2016_03(2015 Q1).csv", "train_2015_11~2016_04(2015 Q1).csv",
"train_2015_12~2016_05(2015 Q1).csv", "train_2016_01-06(2016 Q1).csv", "train_2016_02-07(2016 Q1).csv", "train_2016_03-08(2016 Q1).csv", "train_2016_04-09(2016 Q1).csv", "train_2016_05-10(2016 Q1).csv", "train_2016_06-11(2016 Q1).csv", "train_2016_07-12(2016 Q1).csv", "train_2016_08~2017_01(2016 Q1).csv", "train_2016_09~2017_02(2016 Q1).csv", "train_2016_10~2017_03(2016 Q1).csv", "train_2016_11~2017_04(2016 Q1).csv", "train_2016_12~2017_05(2016 Q1).csv",
"train_2017_01-06(2017 Q1).csv", "train_2017_02-07(2017 Q1).csv", "train_2017_03-08(2017 Q1).csv", "train_2017_04-09(2017 Q1).csv", "train_2017_05-10(2017 Q1).csv", "train_2017_06-11(2017 Q1).csv", "train_2017_07-12(2017 Q1).csv", "train_2017_08~2018_01(2017 Q1).csv", "train_2017_09~2018_02(2017 Q1).csv", "train_2017_10~2018_03(2017 Q1).csv", "train_2017_11~2018_04(2017 Q1).csv", "train_2017_12~2018_05(2017 Q1).csv", "train_2018_01-06(2018 Q1).csv",
"train_2018_02-07(2018 Q1).csv", "train_2018_03-08(2018 Q1).csv", "train_2018_04-09(2018 Q1).csv", "train_2018_05-10(2018 Q1).csv", "train_2018_06-11(2018 Q1).csv", "train_2018_07-12(2018 Q1).csv", "train_2018_08~2019_01(2018 Q1).csv", "train_2018_09~2019_02(2018 Q1).csv", "train_2018_10~2019_03(2018 Q1).csv", "train_2018_11~2019_04(2018 Q1).csv", "train_2018_12~2019_05(2018 Q1).csv", "train_2019_01-06(2019 Q1).csv", "train_2019_02-07(2019 Q1).csv",
"train_2019_03-08(2019 Q1).csv", "train_2019_04-09(2019 Q1).csv", "train_2019_05-10(2019 Q1).csv", "train_2019_06-11(2019 Q1).csv" };
string HH_trainDJI[] = { "train_2009_Q1-Q2(2009 Q1).csv", "train_2009_Q3-Q4(2009 Q1).csv", "train_2010_Q1-Q2(2010 Q1).csv", "train_2010_Q3-Q4(2010 Q1).csv", "train_2011_Q1-Q2(2011 Q1).csv", "train_2011_Q3-Q4(2011 Q1).csv", "train_2012_Q1-Q2(2012 Q1).csv", "train_2012_Q3-Q4(2012 Q1).csv", "train_2013_Q1-Q2(2013 Q1).csv", "train_2013_Q3-Q4(2013 Q1).csv", "train_2014_Q1-Q2(2014 Q1).csv", "train_2014_Q3-Q4(2014 Q1).csv", "train_2015_Q1-Q2(2015 Q1).csv", "train_2015_Q3-Q4(2015 Q1).csv", "train_2016_Q1-Q2(2016 Q1).csv",
"train_2016_Q3-Q4(2016 Q1).csv", "train_2017_Q1-Q2(2017 Q1).csv", "train_2017_Q3-Q4(2017 Q1).csv", "train_2018_Q1-Q2(2018 Q1).csv", "train_2018_Q3-Q4(2018 Q1).csv" };
string H2H_trainDJI[] = { "train_2009_Q3-Q4(2009 Q1).csv", "train_2010_Q1-Q2(2010 Q1).csv", "train_2010_Q3-Q4(2010 Q1).csv", "train_2011_Q1-Q2(2011 Q1).csv", "train_2011_Q3-Q4(2011 Q1).csv", "train_2012_Q1-Q2(2012 Q1).csv", "train_2012_Q3-Q4(2012 Q1).csv", "train_2013_Q1-Q2(2013 Q1).csv", "train_2013_Q3-Q4(2013 Q1).csv", "train_2014_Q1-Q2(2014 Q1).csv", "train_2014_Q3-Q4(2014 Q1).csv", "train_2015_Q1-Q2(2015 Q1).csv", "train_2015_Q3-Q4(2015 Q1).csv", "train_2016_Q1-Q2(2016 Q1).csv","train_2016_Q3-Q4(2016 Q1).csv","train_2017_Q1-Q2(2017 Q1).csv",
"train_2017_Q3-Q4(2017 Q1).csv", "train_2018_Q1-Q2(2018 Q1).csv", "train_2018_Q3-Q4(2018 Q1).csv", "train_2019_Q1-Q2(2019 Q1).csv" };
/*�Dã30�V�m��*/

string Y2Y_testDJI[] = { "test_2010(2009 Q1).csv", "test_2011(2010 Q1).csv", "test_2012(2011 Q1).csv", "test_2013(2012 Q1).csv", "test_2014(2013 Q1).csv", "test_2015(2014 Q1).csv", "test_2016(2015 Q1).csv", "test_2017(2016 Q1).csv", "test_2018(2017 Q1).csv", "test_2019(2018 Q1).csv" };
string Y2Q_testDJI[] = { "test_2010_Q1(2009 Q1).csv", "test_2010_Q2(2009 Q1).csv", "test_2010_Q3(2009 Q1).csv", "test_2010_Q4(2009 Q1).csv", "test_2011_Q1(2010 Q1).csv", "test_2011_Q2(2010 Q1).csv", "test_2011_Q3(2010 Q1).csv", "test_2011_Q4(2010 Q1).csv", "test_2012_Q1(2011 Q1).csv", "test_2012_Q2(2011 Q1).csv", "test_2012_Q3(2011 Q1).csv", "test_2012_Q4(2011 Q1).csv", "test_2013_Q1(2012 Q1).csv", "test_2013_Q2(2012 Q1).csv", "test_2013_Q3(2012 Q1).csv", "test_2013_Q4(2012 Q1).csv",
"test_2014_Q1(2013 Q1).csv","test_2014_Q2(2013 Q1).csv", "test_2014_Q3(2013 Q1).csv", "test_2014_Q4(2013 Q1).csv", "test_2015_Q1(2014 Q1).csv", "test_2015_Q2(2014 Q1).csv", "test_2015_Q3(2014 Q1).csv", "test_2015_Q4(2014 Q1).csv", "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2015 Q1).csv", "test_2016_Q3(2015 Q1).csv", "test_2016_Q4(2015 Q1).csv",
"test_2017_Q1(2016 Q1).csv", "test_2017_Q2(2016 Q1).csv", "test_2017_Q3(2016 Q1).csv", "test_2017_Q4(2016 Q1).csv", "test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2017 Q1).csv", "test_2018_Q3(2017 Q1).csv", "test_2018_Q4(2017 Q1).csv", "test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2018 Q1).csv", "test_2019_Q3(2018 Q1).csv", "test_2019_Q4(2018 Q1).csv" };
string Y2M_testDJI[] = { "test_2010_01(2009 Q1).csv", "test_2010_02(2009 Q1).csv", "test_2010_03(2009 Q1).csv", "test_2010_04(2009 Q1).csv", "test_2010_05(2009 Q1).csv", "test_2010_06(2009 Q1).csv", "test_2010_07(2009 Q1).csv", "test_2010_08(2009 Q1).csv", "test_2010_09(2009 Q1).csv", "test_2010_10(2009 Q1).csv", "test_2010_11(2009 Q1).csv", "test_2010_12(2009 Q1).csv", "test_2011_01(2010 Q1).csv", "test_2011_02(2010 Q1).csv", "test_2011_03(2010 Q1).csv", "test_2011_04(2010 Q1).csv", "test_2011_05(2010 Q1).csv",
"test_2011_06(2010 Q1).csv", "test_2011_07(2010 Q1).csv", "test_2011_08(2010 Q1).csv", "test_2011_09(2010 Q1).csv", "test_2011_10(2010 Q1).csv", "test_2011_11(2010 Q1).csv", "test_2011_12(2010 Q1).csv", "test_2012_01(2011 Q1).csv", "test_2012_02(2011 Q1).csv", "test_2012_03(2011 Q1).csv", "test_2012_04(2011 Q1).csv", "test_2012_05(2011 Q1).csv", "test_2012_06(2011 Q1).csv", "test_2012_07(2011 Q1).csv", "test_2012_08(2011 Q1).csv", "test_2012_09(2011 Q1).csv", "test_2012_10(2011 Q1).csv", "test_2012_11(2011 Q1).csv",
"test_2012_12(2011 Q1).csv", "test_2013_01(2012 Q1).csv", "test_2013_02(2012 Q1).csv", "test_2013_03(2012 Q1).csv", "test_2013_04(2012 Q1).csv", "test_2013_05(2012 Q1).csv", "test_2013_06(2012 Q1).csv", "test_2013_07(2012 Q1).csv", "test_2013_08(2012 Q1).csv", "test_2013_09(2012 Q1).csv", "test_2013_10(2012 Q1).csv", "test_2013_11(2012 Q1).csv", "test_2013_12(2012 Q1).csv", "test_2014_01(2013 Q1).csv", "test_2014_02(2013 Q1).csv", "test_2014_03(2013 Q1).csv", "test_2014_04(2013 Q1).csv", "test_2014_05(2013 Q1).csv",
"test_2014_06(2013 Q1).csv", "test_2014_07(2013 Q1).csv", "test_2014_08(2013 Q1).csv", "test_2014_09(2013 Q1).csv", "test_2014_10(2013 Q1).csv", "test_2014_11(2013 Q1).csv", "test_2014_12(2013 Q1).csv", "test_2015_01(2014 Q1).csv", "test_2015_02(2014 Q1).csv", "test_2015_03(2014 Q1).csv", "test_2015_04(2014 Q1).csv", "test_2015_05(2014 Q1).csv", "test_2015_06(2014 Q1).csv", "test_2015_07(2014 Q1).csv", "test_2015_08(2014 Q1).csv", "test_2015_09(2014 Q1).csv", "test_2015_10(2014 Q1).csv", "test_2015_11(2014 Q1).csv",
"test_2015_12(2014 Q1).csv", "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv", "test_2016_04(2015 Q1).csv", "test_2016_05(2015 Q1).csv", "test_2016_06(2015 Q1).csv", "test_2016_07(2015 Q1).csv", "test_2016_08(2015 Q1).csv", "test_2016_09(2015 Q1).csv", "test_2016_10(2015 Q1).csv", "test_2016_11(2015 Q1).csv", "test_2016_12(2015 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2016 Q1).csv", "test_2017_05(2016 Q1).csv",
"test_2017_06(2016 Q1).csv", "test_2017_07(2016 Q1).csv", "test_2017_08(2016 Q1).csv", "test_2017_09(2016 Q1).csv", "test_2017_10(2016 Q1).csv", "test_2017_11(2016 Q1).csv", "test_2017_12(2016 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2017 Q1).csv", "test_2018_05(2017 Q1).csv", "test_2018_06(2017 Q1).csv", "test_2018_07(2017 Q1).csv", "test_2018_08(2017 Q1).csv", "test_2018_09(2017 Q1).csv", "test_2018_10(2017 Q1).csv", "test_2018_11(2017 Q1).csv",
"test_2018_12(2017 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2018 Q1).csv", "test_2019_05(2018 Q1).csv", "test_2019_06(2018 Q1).csv", "test_2019_07(2018 Q1).csv", "test_2019_08(2018 Q1).csv", "test_2019_09(2018 Q1).csv", "test_2019_10(2018 Q1).csv", "test_2019_11(2018 Q1).csv", "test_2019_12(2018 Q1).csv" };
string Y2H_testDJI[] = { "test_2010_Q1-Q2(2009 Q1).csv", "test_2010_Q3-Q4(2009 Q1).csv", "test_2011_Q1-Q2(2010 Q1).csv", "test_2011_Q3-Q4(2010 Q1).csv", "test_2012_Q1-Q2(2011 Q1).csv", "test_2012_Q3-Q4(2011 Q1).csv", "test_2013_Q1-Q2(2012 Q1).csv", "test_2013_Q3-Q4(2012 Q1).csv", "test_2014_Q1-Q2(2013 Q1).csv", "test_2014_Q3-Q4(2013 Q1).csv", "test_2015_Q1-Q2(2014 Q1).csv", "test_2015_Q3-Q4(2014 Q1).csv", "test_2016_Q1-Q2(2015 Q1).csv", "test_2016_Q3-Q4(2015 Q1).csv", "test_2017_Q1-Q2(2016 Q1).csv", "test_2017_Q3-Q4(2016 Q1).csv", "test_2018_Q1-Q2(2017 Q1).csv", "test_2018_Q3-Q4(2017 Q1).csv", "test_2019_Q1-Q2(2018 Q1).csv", "test_2019_Q3-Q4(2018 Q1).csv" };
string Q2Q_testDJI[] = { "test_2010_Q1(2009 Q1).csv", "test_2010_Q2(2010 Q1).csv", "test_2010_Q3(2010 Q1).csv", "test_2010_Q4(2010 Q1).csv", "test_2011_Q1(2010 Q1).csv", "test_2011_Q2(2011 Q1).csv", "test_2011_Q3(2011 Q1).csv", "test_2011_Q4(2011 Q1).csv", "test_2012_Q1(2011 Q1).csv", "test_2012_Q2(2012 Q1).csv", "test_2012_Q3(2012 Q1).csv", "test_2012_Q4(2012 Q1).csv", "test_2013_Q1(2012 Q1).csv", "test_2013_Q2(2013 Q1).csv", "test_2013_Q3(2013 Q1).csv", "test_2013_Q4(2013 Q1).csv", "test_2014_Q1(2013 Q1).csv", "test_2014_Q2(2014 Q1).csv", "test_2014_Q3(2014 Q1).csv", "test_2014_Q4(2014 Q1).csv", "test_2015_Q1(2014 Q1).csv", "test_2015_Q2(2015 Q1).csv", "test_2015_Q3(2015 Q1).csv", "test_2015_Q4(2015 Q1).csv", "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2016 Q1).csv", "test_2016_Q3(2016 Q1).csv", "test_2016_Q4(2016 Q1).csv", "test_2017_Q1(2016 Q1).csv",
"test_2017_Q2(2017 Q1).csv", "test_2017_Q3(2017 Q1).csv", "test_2017_Q4(2017 Q1).csv", "test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2018 Q1).csv", "test_2018_Q3(2018 Q1).csv", "test_2018_Q4(2018 Q1).csv", "test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2019 Q1).csv", "test_2019_Q3(2019 Q1).csv", "test_2019_Q4(2019 Q1).csv" };
string Q2M_testDJI[] = { "test_2010_01(2009 Q1).csv", "test_2010_02(2009 Q1).csv", "test_2010_03(2009 Q1).csv", "test_2010_04(2010 Q1).csv", "test_2010_05(2010 Q1).csv", "test_2010_06(2010 Q1).csv", "test_2010_07(2010 Q1).csv", "test_2010_08(2010 Q1).csv", "test_2010_09(2010 Q1).csv", "test_2010_10(2010 Q1).csv", "test_2010_11(2010 Q1).csv", "test_2010_12(2010 Q1).csv", "test_2011_01(2010 Q1).csv", "test_2011_02(2010 Q1).csv", "test_2011_03(2010 Q1).csv", "test_2011_04(2011 Q1).csv", "test_2011_05(2011 Q1).csv", "test_2011_06(2011 Q1).csv",
"test_2011_07(2011 Q1).csv", "test_2011_08(2011 Q1).csv", "test_2011_09(2011 Q1).csv", "test_2011_10(2011 Q1).csv", "test_2011_11(2011 Q1).csv", "test_2011_12(2011 Q1).csv", "test_2012_01(2011 Q1).csv", "test_2012_02(2011 Q1).csv", "test_2012_03(2011 Q1).csv", "test_2012_04(2012 Q1).csv", "test_2012_05(2012 Q1).csv", "test_2012_06(2012 Q1).csv", "test_2012_07(2012 Q1).csv", "test_2012_08(2012 Q1).csv", "test_2012_09(2012 Q1).csv", "test_2012_10(2012 Q1).csv", "test_2012_11(2012 Q1).csv", "test_2012_12(2012 Q1).csv", "test_2013_01(2012 Q1).csv",
"test_2013_02(2012 Q1).csv", "test_2013_03(2012 Q1).csv", "test_2013_04(2013 Q1).csv", "test_2013_05(2013 Q1).csv", "test_2013_06(2013 Q1).csv", "test_2013_07(2013 Q1).csv", "test_2013_08(2013 Q1).csv", "test_2013_09(2013 Q1).csv", "test_2013_10(2013 Q1).csv", "test_2013_11(2013 Q1).csv", "test_2013_12(2013 Q1).csv", "test_2014_01(2013 Q1).csv", "test_2014_02(2013 Q1).csv", "test_2014_03(2013 Q1).csv", "test_2014_04(2014 Q1).csv", "test_2014_05(2014 Q1).csv", "test_2014_06(2014 Q1).csv", "test_2014_07(2014 Q1).csv", "test_2014_08(2014 Q1).csv",
"test_2014_09(2014 Q1).csv", "test_2014_10(2014 Q1).csv", "test_2014_11(2014 Q1).csv", "test_2014_12(2014 Q1).csv", "test_2015_01(2014 Q1).csv", "test_2015_02(2014 Q1).csv", "test_2015_03(2014 Q1).csv", "test_2015_04(2015 Q1).csv", "test_2015_05(2015 Q1).csv", "test_2015_06(2015 Q1).csv", "test_2015_07(2015 Q1).csv", "test_2015_08(2015 Q1).csv", "test_2015_09(2015 Q1).csv", "test_2015_10(2015 Q1).csv", "test_2015_11(2015 Q1).csv", "test_2015_12(2015 Q1).csv", "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv",
"test_2016_04(2016 Q1).csv", "test_2016_05(2016 Q1).csv", "test_2016_06(2016 Q1).csv", "test_2016_07(2016 Q1).csv", "test_2016_08(2016 Q1).csv", "test_2016_09(2016 Q1).csv", "test_2016_10(2016 Q1).csv", "test_2016_11(2016 Q1).csv", "test_2016_12(2016 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2017 Q1).csv", "test_2017_05(2017 Q1).csv", "test_2017_06(2017 Q1).csv", "test_2017_07(2017 Q1).csv", "test_2017_08(2017 Q1).csv", "test_2017_09(2017 Q1).csv", "test_2017_10(2017 Q1).csv",
"test_2017_11(2017 Q1).csv", "test_2017_12(2017 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2018 Q1).csv", "test_2018_05(2018 Q1).csv", "test_2018_06(2018 Q1).csv", "test_2018_07(2018 Q1).csv", "test_2018_08(2018 Q1).csv", "test_2018_09(2018 Q1).csv", "test_2018_10(2018 Q1).csv", "test_2018_11(2018 Q1).csv", "test_2018_12(2018 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2019 Q1).csv", "test_2019_05(2019 Q1).csv",
"test_2019_06(2019 Q1).csv", "test_2019_07(2019 Q1).csv", "test_2019_08(2019 Q1).csv", "test_2019_09(2019 Q1).csv", "test_2019_10(2019 Q1).csv", "test_2019_11(2019 Q1).csv", "test_2019_12(2019 Q1).csv" };
string QQ_testDJI[] = { "test_2010_Q1(2009 Q1).csv" ,"test_2010_Q2(2009 Q1).csv", "test_2010_Q3(2009 Q1).csv", "test_2010_Q4(2009 Q1).csv", "test_2011_Q1(2010 Q1).csv", "test_2011_Q2(2010 Q1).csv", "test_2011_Q3(2010 Q1).csv", "test_2011_Q4(2010 Q1).csv", "test_2012_Q1(2011 Q1).csv", "test_2012_Q2(2011 Q1).csv", "test_2012_Q3(2011 Q1).csv", "test_2012_Q4(2011 Q1).csv", "test_2013_Q1(2012 Q1).csv", "test_2013_Q2(2012 Q1).csv", "test_2013_Q3(2012 Q1).csv", "test_2013_Q4(2012 Q1).csv", "test_2014_Q1(2013 Q1).csv", "test_2014_Q2(2013 Q1).csv",
"test_2014_Q3(2013 Q1).csv", "test_2014_Q4(2013 Q1).csv", "test_2015_Q1(2014 Q1).csv", "test_2015_Q2(2014 Q1).csv", "test_2015_Q3(2014 Q1).csv", "test_2015_Q4(2014 Q1).csv", "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2015 Q1).csv", "test_2016_Q3(2015 Q1).csv", "test_2016_Q4(2015 Q1).csv", "test_2017_Q1(2016 Q1).csv", "test_2017_Q2(2016 Q1).csv", "test_2017_Q3(2016 Q1).csv", "test_2017_Q4(2016 Q1).csv", "test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2017 Q1).csv", "test_2018_Q3(2017 Q1).csv", "test_2018_Q4(2017 Q1).csv",
"test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2018 Q1).csv", "test_2019_Q3(2018 Q1).csv", "test_2019_Q4(2018 Q1).csv" };
string M2M_testDJI[] = { "test_2010_01(2009 Q1).csv", "test_2010_02(2010 Q1).csv", "test_2010_03(2010 Q1).csv", "test_2010_04(2010 Q1).csv", "test_2010_05(2010 Q1).csv", "test_2010_06(2010 Q1).csv", "test_2010_07(2010 Q1).csv", "test_2010_08(2010 Q1).csv", "test_2010_09(2010 Q1).csv", "test_2010_10(2010 Q1).csv", "test_2010_11(2010 Q1).csv", "test_2010_12(2010 Q1).csv", "test_2011_01(2010 Q1).csv", "test_2011_02(2011 Q1).csv", "test_2011_03(2011 Q1).csv", "test_2011_04(2011 Q1).csv", "test_2011_05(2011 Q1).csv", "test_2011_06(2011 Q1).csv",
"test_2011_07(2011 Q1).csv", "test_2011_08(2011 Q1).csv", "test_2011_09(2011 Q1).csv", "test_2011_10(2011 Q1).csv", "test_2011_11(2011 Q1).csv", "test_2011_12(2011 Q1).csv", "test_2012_01(2011 Q1).csv", "test_2012_02(2012 Q1).csv", "test_2012_03(2012 Q1).csv", "test_2012_04(2012 Q1).csv", "test_2012_05(2012 Q1).csv", "test_2012_06(2012 Q1).csv", "test_2012_07(2012 Q1).csv", "test_2012_08(2012 Q1).csv", "test_2012_09(2012 Q1).csv", "test_2012_10(2012 Q1).csv", "test_2012_11(2012 Q1).csv", "test_2012_12(2012 Q1).csv", "test_2013_01(2012 Q1).csv",
"test_2013_02(2013 Q1).csv", "test_2013_03(2013 Q1).csv", "test_2013_04(2013 Q1).csv", "test_2013_05(2013 Q1).csv", "test_2013_06(2013 Q1).csv", "test_2013_07(2013 Q1).csv", "test_2013_08(2013 Q1).csv", "test_2013_09(2013 Q1).csv", "test_2013_10(2013 Q1).csv", "test_2013_11(2013 Q1).csv", "test_2013_12(2013 Q1).csv", "test_2014_01(2013 Q1).csv", "test_2014_02(2014 Q1).csv", "test_2014_03(2014 Q1).csv", "test_2014_04(2014 Q1).csv", "test_2014_05(2014 Q1).csv", "test_2014_06(2014 Q1).csv", "test_2014_07(2014 Q1).csv", "test_2014_08(2014 Q1).csv",
"test_2014_09(2014 Q1).csv", "test_2014_10(2014 Q1).csv", "test_2014_11(2014 Q1).csv", "test_2014_12(2014 Q1).csv", "test_2015_01(2014 Q1).csv", "test_2015_02(2015 Q1).csv", "test_2015_03(2015 Q1).csv", "test_2015_04(2015 Q1).csv", "test_2015_05(2015 Q1).csv", "test_2015_06(2015 Q1).csv", "test_2015_07(2015 Q1).csv", "test_2015_08(2015 Q1).csv", "test_2015_09(2015 Q1).csv", "test_2015_10(2015 Q1).csv", "test_2015_11(2015 Q1).csv", "test_2015_12(2015 Q1).csv", "test_2016_01(2015 Q1).csv", "test_2016_02(2016 Q1).csv", "test_2016_03(2016 Q1).csv",
"test_2016_04(2016 Q1).csv", "test_2016_05(2016 Q1).csv", "test_2016_06(2016 Q1).csv", "test_2016_07(2016 Q1).csv", "test_2016_08(2016 Q1).csv", "test_2016_09(2016 Q1).csv", "test_2016_10(2016 Q1).csv", "test_2016_11(2016 Q1).csv", "test_2016_12(2016 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2017 Q1).csv", "test_2017_03(2017 Q1).csv", "test_2017_04(2017 Q1).csv", "test_2017_05(2017 Q1).csv", "test_2017_06(2017 Q1).csv", "test_2017_07(2017 Q1).csv", "test_2017_08(2017 Q1).csv", "test_2017_09(2017 Q1).csv", "test_2017_10(2017 Q1).csv",
"test_2017_11(2017 Q1).csv", "test_2017_12(2017 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2018 Q1).csv", "test_2018_03(2018 Q1).csv", "test_2018_04(2018 Q1).csv", "test_2018_05(2018 Q1).csv", "test_2018_06(2018 Q1).csv", "test_2018_07(2018 Q1).csv", "test_2018_08(2018 Q1).csv", "test_2018_09(2018 Q1).csv", "test_2018_10(2018 Q1).csv", "test_2018_11(2018 Q1).csv", "test_2018_12(2018 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2019 Q1).csv", "test_2019_03(2019 Q1).csv", "test_2019_04(2019 Q1).csv", "test_2019_05(2019 Q1).csv",
"test_2019_06(2019 Q1).csv", "test_2019_07(2019 Q1).csv", "test_2019_08(2019 Q1).csv", "test_2019_09(2019 Q1).csv", "test_2019_10(2019 Q1).csv", "test_2019_11(2019 Q1).csv", "test_2019_12(2019 Q1).csv" };
string MM_testDJI[] = { "test_2010_01(2009 Q1).csv", "test_2010_02(2009 Q1).csv", "test_2010_03(2009 Q1).csv", "test_2010_04(2009 Q1).csv", "test_2010_05(2009 Q1).csv", "test_2010_06(2009 Q1).csv", "test_2010_07(2009 Q1).csv", "test_2010_08(2009 Q1).csv", "test_2010_09(2009 Q1).csv", "test_2010_10(2009 Q1).csv", "test_2010_11(2009 Q1).csv", "test_2010_12(2009 Q1).csv", "test_2011_01(2010 Q1).csv", "test_2011_02(2010 Q1).csv", "test_2011_03(2010 Q1).csv", "test_2011_04(2010 Q1).csv", "test_2011_05(2010 Q1).csv", "test_2011_06(2010 Q1).csv",
"test_2011_07(2010 Q1).csv", "test_2011_08(2010 Q1).csv", "test_2011_09(2010 Q1).csv", "test_2011_10(2010 Q1).csv", "test_2011_11(2010 Q1).csv", "test_2011_12(2010 Q1).csv", "test_2012_01(2011 Q1).csv", "test_2012_02(2011 Q1).csv", "test_2012_03(2011 Q1).csv", "test_2012_04(2011 Q1).csv", "test_2012_05(2011 Q1).csv", "test_2012_06(2011 Q1).csv", "test_2012_07(2011 Q1).csv", "test_2012_08(2011 Q1).csv", "test_2012_09(2011 Q1).csv", "test_2012_10(2011 Q1).csv", "test_2012_11(2011 Q1).csv", "test_2012_12(2011 Q1).csv", "test_2013_01(2012 Q1).csv",
"test_2013_02(2012 Q1).csv", "test_2013_03(2012 Q1).csv", "test_2013_04(2012 Q1).csv", "test_2013_05(2012 Q1).csv", "test_2013_06(2012 Q1).csv", "test_2013_07(2012 Q1).csv", "test_2013_08(2012 Q1).csv", "test_2013_09(2012 Q1).csv", "test_2013_10(2012 Q1).csv", "test_2013_11(2012 Q1).csv", "test_2013_12(2012 Q1).csv", "test_2014_01(2013 Q1).csv", "test_2014_02(2013 Q1).csv", "test_2014_03(2013 Q1).csv", "test_2014_04(2013 Q1).csv", "test_2014_05(2013 Q1).csv", "test_2014_06(2013 Q1).csv", "test_2014_07(2013 Q1).csv", "test_2014_08(2013 Q1).csv",
"test_2014_09(2013 Q1).csv", "test_2014_10(2013 Q1).csv", "test_2014_11(2013 Q1).csv", "test_2014_12(2013 Q1).csv", "test_2015_01(2014 Q1).csv", "test_2015_02(2014 Q1).csv", "test_2015_03(2014 Q1).csv", "test_2015_04(2014 Q1).csv", "test_2015_05(2014 Q1).csv", "test_2015_06(2014 Q1).csv", "test_2015_07(2014 Q1).csv", "test_2015_08(2014 Q1).csv", "test_2015_09(2014 Q1).csv", "test_2015_10(2014 Q1).csv", "test_2015_11(2014 Q1).csv", "test_2015_12(2014 Q1).csv", "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv",
"test_2016_04(2015 Q1).csv", "test_2016_05(2015 Q1).csv", "test_2016_06(2015 Q1).csv", "test_2016_07(2015 Q1).csv", "test_2016_08(2015 Q1).csv", "test_2016_09(2015 Q1).csv", "test_2016_10(2015 Q1).csv", "test_2016_11(2015 Q1).csv", "test_2016_12(2015 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2016 Q1).csv", "test_2017_05(2016 Q1).csv", "test_2017_06(2016 Q1).csv", "test_2017_07(2016 Q1).csv", "test_2017_08(2016 Q1).csv", "test_2017_09(2016 Q1).csv", "test_2017_10(2016 Q1).csv",
"test_2017_11(2016 Q1).csv", "test_2017_12(2016 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2017 Q1).csv", "test_2018_05(2017 Q1).csv", "test_2018_06(2017 Q1).csv", "test_2018_07(2017 Q1).csv", "test_2018_08(2017 Q1).csv", "test_2018_09(2017 Q1).csv", "test_2018_10(2017 Q1).csv", "test_2018_11(2017 Q1).csv", "test_2018_12(2017 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2018 Q1).csv", "test_2019_05(2018 Q1).csv",
"test_2019_06(2018 Q1).csv", "test_2019_07(2018 Q1).csv", "test_2019_08(2018 Q1).csv", "test_2019_09(2018 Q1).csv", "test_2019_10(2018 Q1).csv", "test_2019_11(2018 Q1).csv", "test_2019_12(2018 Q1).csv" };
string H2Q_testDJI[] = { "test_2010_Q1(2009 Q1).csv", "test_2010_Q2(2009 Q1).csv", "test_2010_Q3(2010 Q1).csv", "test_2010_Q4(2010 Q1).csv", "test_2011_Q1(2010 Q1).csv", "test_2011_Q2(2010 Q1).csv", "test_2011_Q3(2011 Q1).csv", "test_2011_Q4(2011 Q1).csv", "test_2012_Q1(2011 Q1).csv", "test_2012_Q2(2011 Q1).csv", "test_2012_Q3(2012 Q1).csv", "test_2012_Q4(2012 Q1).csv", "test_2013_Q1(2012 Q1).csv", "test_2013_Q2(2012 Q1).csv", "test_2013_Q3(2013 Q1).csv", "test_2013_Q4(2013 Q1).csv", "test_2014_Q1(2013 Q1).csv", "test_2014_Q2(2013 Q1).csv","test_2014_Q3(2014 Q1).csv",
"test_2014_Q4(2014 Q1).csv", "test_2015_Q1(2014 Q1).csv", "test_2015_Q2(2014 Q1).csv", "test_2015_Q3(2015 Q1).csv", "test_2015_Q4(2015 Q1).csv", "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2015 Q1).csv", "test_2016_Q3(2016 Q1).csv", "test_2016_Q4(2016 Q1).csv", "test_2017_Q1(2016 Q1).csv", "test_2017_Q2(2016 Q1).csv", "test_2017_Q3(2017 Q1).csv", "test_2017_Q4(2017 Q1).csv",
"test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2017 Q1).csv", "test_2018_Q3(2018 Q1).csv", "test_2018_Q4(2018 Q1).csv", "test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2018 Q1).csv", "test_2019_Q3(2019 Q1).csv", "test_2019_Q4(2019 Q1).csv" };
string H2M_testDJI[] = { "test_2010_01(2009 Q1).csv", "test_2010_02(2009 Q1).csv", "test_2010_03(2009 Q1).csv", "test_2010_04(2009 Q1).csv", "test_2010_05(2009 Q1).csv", "test_2010_06(2009 Q1).csv", "test_2010_07(2010 Q1).csv", "test_2010_08(2010 Q1).csv", "test_2010_09(2010 Q1).csv", "test_2010_10(2010 Q1).csv", "test_2010_11(2010 Q1).csv", "test_2010_12(2010 Q1).csv", "test_2011_01(2010 Q1).csv", "test_2011_02(2010 Q1).csv", "test_2011_03(2010 Q1).csv", "test_2011_04(2010 Q1).csv", "test_2011_05(2010 Q1).csv", "test_2011_06(2010 Q1).csv",
"test_2011_07(2011 Q1).csv", "test_2011_08(2011 Q1).csv", "test_2011_09(2011 Q1).csv", "test_2011_10(2011 Q1).csv", "test_2011_11(2011 Q1).csv", "test_2011_12(2011 Q1).csv", "test_2012_01(2011 Q1).csv", "test_2012_02(2011 Q1).csv", "test_2012_03(2011 Q1).csv", "test_2012_04(2011 Q1).csv", "test_2012_05(2011 Q1).csv", "test_2012_06(2011 Q1).csv", "test_2012_07(2012 Q1).csv", "test_2012_08(2012 Q1).csv", "test_2012_09(2012 Q1).csv", "test_2012_10(2012 Q1).csv", "test_2012_11(2012 Q1).csv", "test_2012_12(2012 Q1).csv", "test_2013_01(2012 Q1).csv",
"test_2013_02(2012 Q1).csv", "test_2013_03(2012 Q1).csv", "test_2013_04(2012 Q1).csv", "test_2013_05(2012 Q1).csv", "test_2013_06(2012 Q1).csv", "test_2013_07(2013 Q1).csv", "test_2013_08(2013 Q1).csv", "test_2013_09(2013 Q1).csv", "test_2013_10(2013 Q1).csv", "test_2013_11(2013 Q1).csv", "test_2013_12(2013 Q1).csv", "test_2014_01(2013 Q1).csv", "test_2014_02(2013 Q1).csv", "test_2014_03(2013 Q1).csv", "test_2014_04(2013 Q1).csv", "test_2014_05(2013 Q1).csv", "test_2014_06(2013 Q1).csv", "test_2014_07(2014 Q1).csv", "test_2014_08(2014 Q1).csv",
"test_2014_09(2014 Q1).csv", "test_2014_10(2014 Q1).csv", "test_2014_11(2014 Q1).csv", "test_2014_12(2014 Q1).csv", "test_2015_01(2014 Q1).csv", "test_2015_02(2014 Q1).csv", "test_2015_03(2014 Q1).csv", "test_2015_04(2014 Q1).csv", "test_2015_05(2014 Q1).csv", "test_2015_06(2014 Q1).csv", "test_2015_07(2015 Q1).csv", "test_2015_08(2015 Q1).csv", "test_2015_09(2015 Q1).csv", "test_2015_10(2015 Q1).csv", "test_2015_11(2015 Q1).csv", "test_2015_12(2015 Q1).csv", "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv",
"test_2016_04(2015 Q1).csv", "test_2016_05(2015 Q1).csv", "test_2016_06(2015 Q1).csv", "test_2016_07(2016 Q1).csv", "test_2016_08(2016 Q1).csv", "test_2016_09(2016 Q1).csv", "test_2016_10(2016 Q1).csv", "test_2016_11(2016 Q1).csv", "test_2016_12(2016 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2016 Q1).csv", "test_2017_05(2016 Q1).csv", "test_2017_06(2016 Q1).csv", "test_2017_07(2017 Q1).csv", "test_2017_08(2017 Q1).csv", "test_2017_09(2017 Q1).csv", "test_2017_10(2017 Q1).csv",
"test_2017_11(2017 Q1).csv", "test_2017_12(2017 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2017 Q1).csv", "test_2018_05(2017 Q1).csv", "test_2018_06(2017 Q1).csv", "test_2018_07(2018 Q1).csv", "test_2018_08(2018 Q1).csv", "test_2018_09(2018 Q1).csv", "test_2018_10(2018 Q1).csv", "test_2018_11(2018 Q1).csv", "test_2018_12(2018 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2018 Q1).csv", "test_2019_05(2018 Q1).csv",
"test_2019_06(2018 Q1).csv", "test_2019_07(2019 Q1).csv", "test_2019_08(2019 Q1).csv", "test_2019_09(2019 Q1).csv", "test_2019_10(2019 Q1).csv", "test_2019_11(2019 Q1).csv", "test_2019_12(2019 Q1).csv" };
string HH_testDJI[] = { "test_2010_Q1-Q2(2009 Q1).csv", "test_2010_Q3-Q4(2009 Q1).csv", "test_2011_Q1-Q2(2010 Q1).csv", "test_2011_Q3-Q4(2010 Q1).csv", "test_2012_Q1-Q2(2011 Q1).csv", "test_2012_Q3-Q4(2011 Q1).csv", "test_2013_Q1-Q2(2012 Q1).csv", "test_2013_Q3-Q4(2012 Q1).csv", "test_2014_Q1-Q2(2013 Q1).csv", "test_2014_Q3-Q4(2013 Q1).csv", "test_2015_Q1-Q2(2014 Q1).csv", "test_2015_Q3-Q4(2014 Q1).csv", "test_2016_Q1-Q2(2015 Q1).csv", "test_2016_Q3-Q4(2015 Q1).csv", "test_2017_Q1-Q2(2016 Q1).csv", "test_2017_Q3-Q4(2016 Q1).csv", "test_2018_Q1-Q2(2017 Q1).csv", "test_2018_Q3-Q4(2017 Q1).csv", "test_2019_Q1-Q2(2018 Q1).csv", "test_2019_Q3-Q4(2018 Q1).csv" };
string H2H_testDJI[] = { "test_2010_Q1-Q2(2009 Q1).csv", "test_2010_Q3-Q4(2010 Q1).csv", "test_2011_Q1-Q2(2010 Q1).csv", "test_2011_Q3-Q4(2011 Q1).csv", "test_2012_Q1-Q2(2011 Q1).csv", "test_2012_Q3-Q4(2012 Q1).csv", "test_2013_Q1-Q2(2012 Q1).csv", "test_2013_Q3-Q4(2013 Q1).csv", "test_2014_Q1-Q2(2013 Q1).csv", "test_2014_Q3-Q4(2014 Q1).csv", "test_2015_Q1-Q2(2014 Q1).csv", "test_2015_Q3-Q4(2015 Q1).csv", "test_2016_Q1-Q2(2015 Q1).csv","test_2016_Q3-Q4(2016 Q1).csv", "test_2017_Q1-Q2(2016 Q1).csv", "test_2017_Q3-Q4(2017 Q1).csv", "test_2018_Q1-Q2(2017 Q1).csv", "test_2018_Q3-Q4(2018 Q1).csv", "test_2019_Q1-Q2(2018 Q1).csv", "test_2019_Q3-Q4(2019 Q1).csv" };
/*�Dã30���մ�*/

string Y2Y_train50[] = { "train_2015(2015 Q1).csv", "train_2016(2016 Q1).csv", "train_2017(2017 Q1).csv", "train_2018(2018 Q1).csv" };
string Y2Q_train50[] = { "train_2015(2015 Q1).csv", "train_2015_Q2~2016_Q1(2015 Q1).csv", "train_2015_Q3~2016_Q2(2015 Q1).csv", "train_2015_Q4~2016_Q3(2015 Q1).csv", "train_2016(2016 Q1).csv", "train_2016_Q2~2017_Q1(2016 Q1).csv", "train_2016_Q3~2017_Q2(2016 Q1).csv", "train_2016_Q4~2017_Q3(2016 Q1).csv",
"train_2017(2017 Q1).csv", "train_2017_Q2~2018_Q1(2017 Q1).csv", "train_2017_Q3~2018_Q2(2017 Q1).csv", "train_2017_Q4~2018_Q3(2017 Q1).csv", "train_2018(2018 Q1).csv", "train_2018_Q2~2019_Q1(2018 Q1).csv", "train_2018_Q3~2019_Q2(2018 Q1).csv", "train_2018_Q4~2019_Q3(2018 Q1).csv" };
string Y2M_train50[] = { "train_2015(2015 Q1).csv", "train_2015_02~2016_01(2015 Q1).csv", "train_2015_03~2016_02(2015 Q1).csv", "train_2015_04~2016_03(2015 Q1).csv", "train_2015_05~2016_04(2015 Q1).csv", "train_2015_06~2016_05(2015 Q1).csv", "train_2015_07~2016_06(2015 Q1).csv", "train_2015_08~2016_07(2015 Q1).csv", "train_2015_09~2016_08(2015 Q1).csv", "train_2015_10~2016_09(2015 Q1).csv", "train_2015_11~2016_10(2015 Q1).csv", "train_2015_12~2016_11(2015 Q1).csv",
"train_2016(2016 Q1).csv", "train_2016_02~2017_01(2016 Q1).csv", "train_2016_03~2017_02(2016 Q1).csv", "train_2016_04~2017_03(2016 Q1).csv", "train_2016_05~2017_04(2016 Q1).csv", "train_2016_06~2017_05(2016 Q1).csv", "train_2016_07~2017_06(2016 Q1).csv", "train_2016_08~2017_07(2016 Q1).csv", "train_2016_09~2017_08(2016 Q1).csv", "train_2016_10~2017_09(2016 Q1).csv", "train_2016_11~2017_10(2016 Q1).csv", "train_2016_12~2017_11(2016 Q1).csv",
"train_2017(2017 Q1).csv", "train_2017_02~2018_01(2017 Q1).csv", "train_2017_03~2018_02(2017 Q1).csv", "train_2017_04~2018_03(2017 Q1).csv", "train_2017_05~2018_04(2017 Q1).csv", "train_2017_06~2018_05(2017 Q1).csv", "train_2017_07~2018_06(2017 Q1).csv", "train_2017_08~2018_07(2017 Q1).csv", "train_2017_09~2018_08(2017 Q1).csv", "train_2017_10~2018_09(2017 Q1).csv", "train_2017_11~2018_10(2017 Q1).csv", "train_2017_12~2018_11(2017 Q1).csv",
"train_2018(2018 Q1).csv", "train_2018_02~2019_01(2018 Q1).csv", "train_2018_03~2019_02(2018 Q1).csv", "train_2018_04~2019_03(2018 Q1).csv", "train_2018_05~2019_04(2018 Q1).csv", "train_2018_06~2019_05(2018 Q1).csv", "train_2018_07~2019_06(2018 Q1).csv", "train_2018_08~2019_07(2018 Q1).csv", "train_2018_09~2019_08(2018 Q1).csv", "train_2018_10~2019_09(2018 Q1).csv", "train_2018_11~2019_10(2018 Q1).csv", "train_2018_12~2019_11(2018 Q1).csv" };
string Y2H_train50[] = { "train_2015(2015 Q1).csv", "train_2015_Q3~2016_Q2(2015 Q1).csv", "train_2016(2016 Q1).csv", "train_2016_Q3~2017_Q2(2016 Q1).csv", "train_2017(2017 Q1).csv", "train_2017_Q3~2018_Q2(2017 Q1).csv", "train_2018(2018 Q1).csv", "train_2018_Q3~2019_Q2(2018 Q1).csv" };
string Q2Q_train50[] = { "train_2015_Q4(2015 Q1).csv", "train_2016_Q1(2016 Q1).csv", "train_2016_Q2(2016 Q1).csv", "train_2016_Q3(2016 Q1).csv", "train_2016_Q4(2016 Q1).csv", "train_2017_Q1(2017 Q1).csv", "train_2017_Q2(2017 Q1).csv", "train_2017_Q3(2017 Q1).csv", "train_2017_Q4(2017 Q1).csv", "train_2018_Q1(2018 Q1).csv", "train_2018_Q2(2018 Q1).csv", "train_2018_Q3(2018 Q1).csv", "train_2018_Q4(2018 Q1).csv", "train_2019_Q1(2019 Q1).csv",
"train_2019_Q2(2019 Q1).csv", "train_2019_Q3(2019 Q1).csv" };
string Q2M_train50[] = { "train_2015_10-12(2015 Q1).csv", "train_2015_11~2016_01(2015 Q1).csv", "train_2015_12~2016_02(2015 Q1).csv", "train_2016_01-03(2016 Q1).csv", "train_2016_02-04(2016 Q1).csv", "train_2016_03-05(2016 Q1).csv", "train_2016_04-06(2016 Q1).csv", "train_2016_05-07(2016 Q1).csv", "train_2016_06-08(2016 Q1).csv", "train_2016_07-09(2016 Q1).csv", "train_2016_08-10(2016 Q1).csv", "train_2016_09-11(2016 Q1).csv",
"train_2016_10-12(2016 Q1).csv", "train_2016_11~2017_01(2016 Q1).csv", "train_2016_12~2017_02(2016 Q1).csv", "train_2017_01-03(2017 Q1).csv", "train_2017_02-04(2017 Q1).csv", "train_2017_03-05(2017 Q1).csv", "train_2017_04-06(2017 Q1).csv", "train_2017_05-07(2017 Q1).csv", "train_2017_06-08(2017 Q1).csv", "train_2017_07-09(2017 Q1).csv", "train_2017_08-10(2017 Q1).csv", "train_2017_09-11(2017 Q1).csv", "train_2017_10-12(2017 Q1).csv", "train_2017_11~2018_01(2017 Q1).csv",
"train_2017_12~2018_02(2017 Q1).csv", "train_2018_01-03(2018 Q1).csv", "train_2018_02-04(2018 Q1).csv", "train_2018_03-05(2018 Q1).csv", "train_2018_04-06(2018 Q1).csv", "train_2018_05-07(2018 Q1).csv", "train_2018_06-08(2018 Q1).csv", "train_2018_07-09(2018 Q1).csv", "train_2018_08-10(2018 Q1).csv", "train_2018_09-11(2018 Q1).csv", "train_2018_10-12(2018 Q1).csv", "train_2018_11~2019_01(2018 Q1).csv", "train_2018_12~2019_02(2018 Q1).csv", "train_2019_01-03(2019 Q1).csv", "train_2019_02-04(2019 Q1).csv",
"train_2019_03-05(2019 Q1).csv", "train_2019_04-06(2019 Q1).csv", "train_2019_05-07(2019 Q1).csv", "train_2019_06-08(2019 Q1).csv", "train_2019_07-09(2019 Q1).csv", "train_2019_08-10(2019 Q1).csv", "train_2019_09-11(2019 Q1).csv" };
string QQ_train50[] = { "train_2015_Q1(2015 Q1).csv", "train_2015_Q2(2015 Q1).csv", "train_2015_Q3(2015 Q1).csv", "train_2015_Q4(2015 Q1).csv", "train_2016_Q1(2016 Q1).csv", "train_2016_Q2(2016 Q1).csv", "train_2016_Q3(2016 Q1).csv", "train_2016_Q4(2016 Q1).csv", "train_2017_Q1(2017 Q1).csv", "train_2017_Q2(2017 Q1).csv", "train_2017_Q3(2017 Q1).csv", "train_2017_Q4(2017 Q1).csv", "train_2018_Q1(2018 Q1).csv", "train_2018_Q2(2018 Q1).csv", "train_2018_Q3(2018 Q1).csv", "train_2018_Q4(2018 Q1).csv" };
string M2M_train50[] = { "train_2015_12(2015 Q1).csv", "train_2016_01(2016 Q1).csv", "train_2016_02(2016 Q1).csv", "train_2016_03(2016 Q1).csv", "train_2016_04(2016 Q1).csv", "train_2016_05(2016 Q1).csv", "train_2016_06(2016 Q1).csv", "train_2016_07(2016 Q1).csv", "train_2016_08(2016 Q1).csv", "train_2016_09(2016 Q1).csv", "train_2016_10(2016 Q1).csv", "train_2016_11(2016 Q1).csv",
"train_2016_12(2016 Q1).csv", "train_2017_01(2017 Q1).csv", "train_2017_02(2017 Q1).csv", "train_2017_03(2017 Q1).csv", "train_2017_04(2017 Q1).csv", "train_2017_05(2017 Q1).csv", "train_2017_06(2017 Q1).csv", "train_2017_07(2017 Q1).csv", "train_2017_08(2017 Q1).csv", "train_2017_09(2017 Q1).csv", "train_2017_10(2017 Q1).csv", "train_2017_11(2017 Q1).csv", "train_2017_12(2017 Q1).csv", "train_2018_01(2018 Q1).csv",
"train_2018_02(2018 Q1).csv", "train_2018_03(2018 Q1).csv", "train_2018_04(2018 Q1).csv", "train_2018_05(2018 Q1).csv", "train_2018_06(2018 Q1).csv", "train_2018_07(2018 Q1).csv", "train_2018_08(2018 Q1).csv", "train_2018_09(2018 Q1).csv", "train_2018_10(2018 Q1).csv", "train_2018_11(2018 Q1).csv", "train_2018_12(2018 Q1).csv", "train_2019_01(2019 Q1).csv", "train_2019_02(2019 Q1).csv", "train_2019_03(2019 Q1).csv",
"train_2019_04(2019 Q1).csv", "train_2019_05(2019 Q1).csv", "train_2019_06(2019 Q1).csv", "train_2019_07(2019 Q1).csv", "train_2019_08(2019 Q1).csv", "train_2019_09(2019 Q1).csv", "train_2019_10(2019 Q1).csv", "train_2019_11(2019 Q1).csv" };
string MM_train50[] = { "train_2015_01(2015 Q1).csv", "train_2015_02(2015 Q1).csv", "train_2015_03(2015 Q1).csv", "train_2015_04(2015 Q1).csv", "train_2015_05(2015 Q1).csv", "train_2015_06(2015 Q1).csv", "train_2015_07(2015 Q1).csv", "train_2015_08(2015 Q1).csv", "train_2015_09(2015 Q1).csv", "train_2015_10(2015 Q1).csv", "train_2015_11(2015 Q1).csv", "train_2015_12(2015 Q1).csv", "train_2016_01(2016 Q1).csv",
"train_2016_02(2016 Q1).csv", "train_2016_03(2016 Q1).csv", "train_2016_04(2016 Q1).csv", "train_2016_05(2016 Q1).csv", "train_2016_06(2016 Q1).csv", "train_2016_07(2016 Q1).csv", "train_2016_08(2016 Q1).csv", "train_2016_09(2016 Q1).csv", "train_2016_10(2016 Q1).csv", "train_2016_11(2016 Q1).csv", "train_2016_12(2016 Q1).csv", "train_2017_01(2017 Q1).csv", "train_2017_02(2017 Q1).csv", "train_2017_03(2017 Q1).csv", "train_2017_04(2017 Q1).csv", "train_2017_05(2017 Q1).csv", "train_2017_06(2017 Q1).csv",
"train_2017_07(2017 Q1).csv", "train_2017_08(2017 Q1).csv", "train_2017_09(2017 Q1).csv", "train_2017_10(2017 Q1).csv", "train_2017_11(2017 Q1).csv", "train_2017_12(2017 Q1).csv", "train_2018_01(2018 Q1).csv", "train_2018_02(2018 Q1).csv", "train_2018_03(2018 Q1).csv", "train_2018_04(2018 Q1).csv", "train_2018_05(2018 Q1).csv", "train_2018_06(2018 Q1).csv", "train_2018_07(2018 Q1).csv", "train_2018_08(2018 Q1).csv", "train_2018_09(2018 Q1).csv", "train_2018_10(2018 Q1).csv", "train_2018_11(2018 Q1).csv",
"train_2018_12(2018 Q1).csv" };
string H2Q_train50[] = { "train_2015_Q3-Q4(2015 Q1).csv", "train_2015_Q4~2016_Q1(2015 Q1).csv", "train_2016_Q1-Q2(2016 Q1).csv", "train_2016_Q2-Q3(2016 Q1).csv", "train_2016_Q3-Q4(2016 Q1).csv", "train_2016_Q4~2017_Q1(2016 Q1).csv", "train_2017_Q1-Q2(2017 Q1).csv", "train_2017_Q2-Q3(2017 Q1).csv", "train_2017_Q3-Q4(2017 Q1).csv", "train_2017_Q4~2018_Q1(2017 Q1).csv", "train_2018_Q1-Q2(2018 Q1).csv", "train_2018_Q2-Q3(2018 Q1).csv", "train_2018_Q3-Q4(2018 Q1).csv", "train_2018_Q4~2019_Q1(2018 Q1).csv",
"train_2019_Q1-Q2(2019 Q1).csv", "train_2019_Q2-Q3(2019 Q1).csv" };
string H2M_train50[] = { "train_2015_07-12(2015 Q1).csv", "train_2015_08~2016_01(2015 Q1).csv", "train_2015_09~2016_02(2015 Q1).csv", "train_2015_10~2016_03(2015 Q1).csv", "train_2015_11~2016_04(2015 Q1).csv",
"train_2015_12~2016_05(2015 Q1).csv", "train_2016_01-06(2016 Q1).csv", "train_2016_02-07(2016 Q1).csv", "train_2016_03-08(2016 Q1).csv", "train_2016_04-09(2016 Q1).csv", "train_2016_05-10(2016 Q1).csv", "train_2016_06-11(2016 Q1).csv", "train_2016_07-12(2016 Q1).csv", "train_2016_08~2017_01(2016 Q1).csv", "train_2016_09~2017_02(2016 Q1).csv", "train_2016_10~2017_03(2016 Q1).csv", "train_2016_11~2017_04(2016 Q1).csv", "train_2016_12~2017_05(2016 Q1).csv",
"train_2017_01-06(2017 Q1).csv", "train_2017_02-07(2017 Q1).csv", "train_2017_03-08(2017 Q1).csv", "train_2017_04-09(2017 Q1).csv", "train_2017_05-10(2017 Q1).csv", "train_2017_06-11(2017 Q1).csv", "train_2017_07-12(2017 Q1).csv", "train_2017_08~2018_01(2017 Q1).csv", "train_2017_09~2018_02(2017 Q1).csv", "train_2017_10~2018_03(2017 Q1).csv", "train_2017_11~2018_04(2017 Q1).csv", "train_2017_12~2018_05(2017 Q1).csv", "train_2018_01-06(2018 Q1).csv",
"train_2018_02-07(2018 Q1).csv", "train_2018_03-08(2018 Q1).csv", "train_2018_04-09(2018 Q1).csv", "train_2018_05-10(2018 Q1).csv", "train_2018_06-11(2018 Q1).csv", "train_2018_07-12(2018 Q1).csv", "train_2018_08~2019_01(2018 Q1).csv", "train_2018_09~2019_02(2018 Q1).csv", "train_2018_10~2019_03(2018 Q1).csv", "train_2018_11~2019_04(2018 Q1).csv", "train_2018_12~2019_05(2018 Q1).csv", "train_2019_01-06(2019 Q1).csv", "train_2019_02-07(2019 Q1).csv",
"train_2019_03-08(2019 Q1).csv", "train_2019_04-09(2019 Q1).csv", "train_2019_05-10(2019 Q1).csv", "train_2019_06-11(2019 Q1).csv" };
string HH_train50[] = { "train_2015_Q1-Q2(2015 Q1).csv", "train_2015_Q3-Q4(2015 Q1).csv", "train_2016_Q1-Q2(2016 Q1).csv", "train_2016_Q3-Q4(2016 Q1).csv", "train_2017_Q1-Q2(2017 Q1).csv", "train_2017_Q3-Q4(2017 Q1).csv", "train_2018_Q1-Q2(2018 Q1).csv", "train_2018_Q3-Q4(2018 Q1).csv" };
string H2H_train50[] = { "train_2015_Q3-Q4(2015 Q1).csv", "train_2016_Q1-Q2(2016 Q1).csv","train_2016_Q3-Q4(2016 Q1).csv","train_2017_Q1-Q2(2017 Q1).csv", "train_2017_Q3-Q4(2017 Q1).csv", "train_2018_Q1-Q2(2018 Q1).csv", "train_2018_Q3-Q4(2018 Q1).csv", "train_2019_Q1-Q2(2019 Q1).csv" };
/*���ȫe50�j�V�m��*/

string Y2Y_test50[] = { "test_2016(2015 Q1).csv", "test_2017(2016 Q1).csv", "test_2018(2017 Q1).csv", "test_2019(2018 Q1).csv" };
string Y2Q_test50[] = { "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2015 Q1).csv", "test_2016_Q3(2015 Q1).csv", "test_2016_Q4(2015 Q1).csv", "test_2017_Q1(2016 Q1).csv", "test_2017_Q2(2016 Q1).csv", "test_2017_Q3(2016 Q1).csv", "test_2017_Q4(2016 Q1).csv", "test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2017 Q1).csv", "test_2018_Q3(2017 Q1).csv", "test_2018_Q4(2017 Q1).csv", "test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2018 Q1).csv", "test_2019_Q3(2018 Q1).csv", "test_2019_Q4(2018 Q1).csv" };
string Y2M_test50[] = { "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv", "test_2016_04(2015 Q1).csv", "test_2016_05(2015 Q1).csv", "test_2016_06(2015 Q1).csv", "test_2016_07(2015 Q1).csv", "test_2016_08(2015 Q1).csv", "test_2016_09(2015 Q1).csv", "test_2016_10(2015 Q1).csv", "test_2016_11(2015 Q1).csv", "test_2016_12(2015 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2016 Q1).csv", "test_2017_05(2016 Q1).csv",
"test_2017_06(2016 Q1).csv", "test_2017_07(2016 Q1).csv", "test_2017_08(2016 Q1).csv", "test_2017_09(2016 Q1).csv", "test_2017_10(2016 Q1).csv", "test_2017_11(2016 Q1).csv", "test_2017_12(2016 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2017 Q1).csv", "test_2018_05(2017 Q1).csv", "test_2018_06(2017 Q1).csv", "test_2018_07(2017 Q1).csv", "test_2018_08(2017 Q1).csv", "test_2018_09(2017 Q1).csv", "test_2018_10(2017 Q1).csv", "test_2018_11(2017 Q1).csv",
"test_2018_12(2017 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2018 Q1).csv", "test_2019_05(2018 Q1).csv", "test_2019_06(2018 Q1).csv", "test_2019_07(2018 Q1).csv", "test_2019_08(2018 Q1).csv", "test_2019_09(2018 Q1).csv", "test_2019_10(2018 Q1).csv", "test_2019_11(2018 Q1).csv", "test_2019_12(2018 Q1).csv" };
string Y2H_test50[] = { "test_2016_Q1-Q2(2015 Q1).csv", "test_2016_Q3-Q4(2015 Q1).csv", "test_2017_Q1-Q2(2016 Q1).csv", "test_2017_Q3-Q4(2016 Q1).csv", "test_2018_Q1-Q2(2017 Q1).csv", "test_2018_Q3-Q4(2017 Q1).csv", "test_2019_Q1-Q2(2018 Q1).csv", "test_2019_Q3-Q4(2018 Q1).csv" };
string Q2Q_test50[] = { "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2016 Q1).csv", "test_2016_Q3(2016 Q1).csv", "test_2016_Q4(2016 Q1).csv", "test_2017_Q1(2016 Q1).csv", "test_2017_Q2(2017 Q1).csv", "test_2017_Q3(2017 Q1).csv", "test_2017_Q4(2017 Q1).csv", "test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2018 Q1).csv", "test_2018_Q3(2018 Q1).csv", "test_2018_Q4(2018 Q1).csv", "test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2019 Q1).csv", "test_2019_Q3(2019 Q1).csv", "test_2019_Q4(2019 Q1).csv" };
string Q2M_test50[] = { "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv",
"test_2016_04(2016 Q1).csv", "test_2016_05(2016 Q1).csv", "test_2016_06(2016 Q1).csv", "test_2016_07(2016 Q1).csv", "test_2016_08(2016 Q1).csv", "test_2016_09(2016 Q1).csv", "test_2016_10(2016 Q1).csv", "test_2016_11(2016 Q1).csv", "test_2016_12(2016 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2017 Q1).csv", "test_2017_05(2017 Q1).csv", "test_2017_06(2017 Q1).csv", "test_2017_07(2017 Q1).csv", "test_2017_08(2017 Q1).csv", "test_2017_09(2017 Q1).csv", "test_2017_10(2017 Q1).csv",
"test_2017_11(2017 Q1).csv", "test_2017_12(2017 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2018 Q1).csv", "test_2018_05(2018 Q1).csv", "test_2018_06(2018 Q1).csv", "test_2018_07(2018 Q1).csv", "test_2018_08(2018 Q1).csv", "test_2018_09(2018 Q1).csv", "test_2018_10(2018 Q1).csv", "test_2018_11(2018 Q1).csv", "test_2018_12(2018 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2019 Q1).csv", "test_2019_05(2019 Q1).csv",
"test_2019_06(2019 Q1).csv", "test_2019_07(2019 Q1).csv", "test_2019_08(2019 Q1).csv", "test_2019_09(2019 Q1).csv", "test_2019_10(2019 Q1).csv", "test_2019_11(2019 Q1).csv", "test_2019_12(2019 Q1).csv" };
string QQ_test50[] = { "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2015 Q1).csv", "test_2016_Q3(2015 Q1).csv", "test_2016_Q4(2015 Q1).csv", "test_2017_Q1(2016 Q1).csv", "test_2017_Q2(2016 Q1).csv", "test_2017_Q3(2016 Q1).csv", "test_2017_Q4(2016 Q1).csv", "test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2017 Q1).csv", "test_2018_Q3(2017 Q1).csv", "test_2018_Q4(2017 Q1).csv",
"test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2018 Q1).csv", "test_2019_Q3(2018 Q1).csv", "test_2019_Q4(2018 Q1).csv" };
string M2M_test50[] = { "test_2016_01(2015 Q1).csv", "test_2016_02(2016 Q1).csv", "test_2016_03(2016 Q1).csv", "test_2016_04(2016 Q1).csv", "test_2016_05(2016 Q1).csv", "test_2016_06(2016 Q1).csv", "test_2016_07(2016 Q1).csv", "test_2016_08(2016 Q1).csv", "test_2016_09(2016 Q1).csv", "test_2016_10(2016 Q1).csv", "test_2016_11(2016 Q1).csv", "test_2016_12(2016 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2017 Q1).csv", "test_2017_03(2017 Q1).csv", "test_2017_04(2017 Q1).csv", "test_2017_05(2017 Q1).csv", "test_2017_06(2017 Q1).csv", "test_2017_07(2017 Q1).csv", "test_2017_08(2017 Q1).csv", "test_2017_09(2017 Q1).csv", "test_2017_10(2017 Q1).csv",
"test_2017_11(2017 Q1).csv", "test_2017_12(2017 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2018 Q1).csv", "test_2018_03(2018 Q1).csv", "test_2018_04(2018 Q1).csv", "test_2018_05(2018 Q1).csv", "test_2018_06(2018 Q1).csv", "test_2018_07(2018 Q1).csv", "test_2018_08(2018 Q1).csv", "test_2018_09(2018 Q1).csv", "test_2018_10(2018 Q1).csv", "test_2018_11(2018 Q1).csv", "test_2018_12(2018 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2019 Q1).csv", "test_2019_03(2019 Q1).csv", "test_2019_04(2019 Q1).csv", "test_2019_05(2019 Q1).csv",
"test_2019_06(2019 Q1).csv", "test_2019_07(2019 Q1).csv", "test_2019_08(2019 Q1).csv", "test_2019_09(2019 Q1).csv", "test_2019_10(2019 Q1).csv", "test_2019_11(2019 Q1).csv", "test_2019_12(2019 Q1).csv" };
string MM_test50[] = { "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv",
"test_2016_04(2015 Q1).csv", "test_2016_05(2015 Q1).csv", "test_2016_06(2015 Q1).csv", "test_2016_07(2015 Q1).csv", "test_2016_08(2015 Q1).csv", "test_2016_09(2015 Q1).csv", "test_2016_10(2015 Q1).csv", "test_2016_11(2015 Q1).csv", "test_2016_12(2015 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2016 Q1).csv", "test_2017_05(2016 Q1).csv", "test_2017_06(2016 Q1).csv", "test_2017_07(2016 Q1).csv", "test_2017_08(2016 Q1).csv", "test_2017_09(2016 Q1).csv", "test_2017_10(2016 Q1).csv",
"test_2017_11(2016 Q1).csv", "test_2017_12(2016 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2017 Q1).csv", "test_2018_05(2017 Q1).csv", "test_2018_06(2017 Q1).csv", "test_2018_07(2017 Q1).csv", "test_2018_08(2017 Q1).csv", "test_2018_09(2017 Q1).csv", "test_2018_10(2017 Q1).csv", "test_2018_11(2017 Q1).csv", "test_2018_12(2017 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2018 Q1).csv", "test_2019_05(2018 Q1).csv",
"test_2019_06(2018 Q1).csv", "test_2019_07(2018 Q1).csv", "test_2019_08(2018 Q1).csv", "test_2019_09(2018 Q1).csv", "test_2019_10(2018 Q1).csv", "test_2019_11(2018 Q1).csv", "test_2019_12(2018 Q1).csv" };
string H2Q_test50[] = { "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2015 Q1).csv", "test_2016_Q3(2016 Q1).csv", "test_2016_Q4(2016 Q1).csv", "test_2017_Q1(2016 Q1).csv", "test_2017_Q2(2016 Q1).csv", "test_2017_Q3(2017 Q1).csv", "test_2017_Q4(2017 Q1).csv",
"test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2017 Q1).csv", "test_2018_Q3(2018 Q1).csv", "test_2018_Q4(2018 Q1).csv", "test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2018 Q1).csv", "test_2019_Q3(2019 Q1).csv", "test_2019_Q4(2019 Q1).csv" };
string H2M_test50[] = { "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv",
"test_2016_04(2015 Q1).csv", "test_2016_05(2015 Q1).csv", "test_2016_06(2015 Q1).csv", "test_2016_07(2016 Q1).csv", "test_2016_08(2016 Q1).csv", "test_2016_09(2016 Q1).csv", "test_2016_10(2016 Q1).csv", "test_2016_11(2016 Q1).csv", "test_2016_12(2016 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2016 Q1).csv", "test_2017_05(2016 Q1).csv", "test_2017_06(2016 Q1).csv", "test_2017_07(2017 Q1).csv", "test_2017_08(2017 Q1).csv", "test_2017_09(2017 Q1).csv", "test_2017_10(2017 Q1).csv",
"test_2017_11(2017 Q1).csv", "test_2017_12(2017 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2017 Q1).csv", "test_2018_05(2017 Q1).csv", "test_2018_06(2017 Q1).csv", "test_2018_07(2018 Q1).csv", "test_2018_08(2018 Q1).csv", "test_2018_09(2018 Q1).csv", "test_2018_10(2018 Q1).csv", "test_2018_11(2018 Q1).csv", "test_2018_12(2018 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2018 Q1).csv", "test_2019_05(2018 Q1).csv",
"test_2019_06(2018 Q1).csv", "test_2019_07(2019 Q1).csv", "test_2019_08(2019 Q1).csv", "test_2019_09(2019 Q1).csv", "test_2019_10(2019 Q1).csv", "test_2019_11(2019 Q1).csv", "test_2019_12(2019 Q1).csv" };
string HH_test50[] = { "test_2016_Q1-Q2(2015 Q1).csv", "test_2016_Q3-Q4(2015 Q1).csv", "test_2017_Q1-Q2(2016 Q1).csv", "test_2017_Q3-Q4(2016 Q1).csv", "test_2018_Q1-Q2(2017 Q1).csv", "test_2018_Q3-Q4(2017 Q1).csv", "test_2019_Q1-Q2(2018 Q1).csv","test_2019_Q3-Q4(2018 Q1).csv" };
string H2H_test50[] = { "test_2016_Q1-Q2(2015 Q1).csv","test_2016_Q3-Q4(2016 Q1).csv", "test_2017_Q1-Q2(2016 Q1).csv", "test_2017_Q3-Q4(2017 Q1).csv", "test_2018_Q1-Q2(2017 Q1).csv", "test_2018_Q3-Q4(2018 Q1).csv", "test_2019_Q1-Q2(2018 Q1).csv", "test_2019_Q3-Q4(2019 Q1).csv" };
/*���ȫe50�j���մ�*/

double all_single_trend_ratio[file_num][partical_num];//�C�Ӱ϶��Ƨǫ᪺�����Ͷխ�
double all_all_trend_ratio[file_num][partical_num];//���Ƨǫ�U�϶������Ͷխ�
double single_trend_ratio[partical_num];
string all_stock_no[file_num][partical_num];
double all_single_m[file_num][partical_num];
double all_single_risk[file_num][partical_num];
double average_risk = 0;
double average_return = 0;
double average_trend_ratio = 0;
double total_return = 0;
double total_risk = 0;
double total_trend_ratio = 0;


double sharpe_ratio[10];//�L����
double sharpe_ratio_risk[10];//�L���ȭ��I
double sharpe_ratio_return[10];//�L���ȳ��S
double risk_free = 0.0087;//�x�ѵL���I�Q�v
double funds_std_total[10];
double average_funds_std[10];
double roi[10];
double funds_std_standard_deviation[10];
double real_all_sharpe_ratio[50][10000][10];
double all_sp_risk[50][10000][10];
double all_sp_return[50][10000][10];
double all_file_best_sp[200];
double test_roi;
double all_test_roi;
double test_funds_std_standard_deviation;
double test_average_funds_std;
double test_sharpe_ratio;//�L����
double test_sharpe_ratio_risk;//�L���ȭ��I
double test_sharpe_ratio_return;//�L���ȳ��S
double all_test_sharpe_ratio;//�L����
double all_test_sharpe_ratio_risk;//�L���ȭ��I
double all_test_sharpe_ratio_return;//�L���ȳ��S
double all_test_funds_std_standard_deviation;
double all_test_average_funds_std;
/*�L���ȫŧi*/

double max_sharpe_ratio;
double min_sharpe_ratio;
int max_sharpe_ratio_tmp;
int min_sharpe_ratio_tmp;
double all_max_sharpe_ratio;
double all_sharpe_ratio_max_tmp[50];
double Gbest_max_sp;
int final_max_tmp[50];
double test_funds_std_total;
double all_test_funds_std_total = 0;
double final_test_period_sharpe_ratio[200];
double final_test_period_sharpe_ratio_risk[200];
double final_test_period_sharpe_return[200];
double all_test_period_std[5000];

void read_file(int a) {
	input_file.open(HH_train50[a], ios::in);
	cout << endl << HH_train50[a] << endl;
	string line;
	while (getline(input_file, line))
	{
		s_stock_index = 0;
		string tmp;
		stringstream ss(line);
		if (index == 0)
		{
			while (getline(ss, tmp, ','))
			{
				string num;
				num = tmp;
				stock_no[s_stock_index] = num; //�s��
											   //cout << stock_no[s_stock_index] << endl;
				s_stock_index++;
			}
			index++;
		}
		else if (index > 0)
		{
			s_stock_index = 0;
			while (getline(ss, tmp, ','))
			{
				stringstream price;
				price << tmp;
				price >> all_stock[s_stock_index][index - 1];//�ѻ�
				s_stock_index++;
			}
			index++;
		}
	}
	input_file.close();
	day = index - 1;
	//cout << day;
}//Ū��

void test_read_file(int a) {

	test_input_file.open(HH_test50[a], ios::in);
	cout << endl << HH_test50[a] << endl;
	string test_line;
	while (getline(test_input_file, test_line))
	{
		test_stock_index = 0;
		string test_tmp;
		stringstream test_ss(test_line);
		if (test_index == 0)
		{
			while (getline(test_ss, test_tmp, ','))
			{
				stringstream test_num;
				test_num << test_tmp;
				test_num >> test_stock_no[test_stock_index];//�s��
															//cout << test_stock_no[test_stock_index] << endl;
				test_stock_index++;
			}
			test_index++;
		}
		else if (test_index > 0)
		{
			test_stock_index = 0;
			while (getline(test_ss, test_tmp, ','))
			{
				stringstream test_price;
				test_price << test_tmp;
				test_price >> test_all_stock[test_stock_index][test_index - 1];//�ѻ�
				test_stock_index++;
			}
			test_index++;
		}
	}
	test_input_file.close();
	test_day = test_index - 1;
	total_test_day += test_day;
}//Ū��

void initial()
{
	for (int i = 0; i < s_stock_index; i++)
	{
		beta[i] = 0.5;
	}
}

void  measure()
{
	//cout << s_stock_index << endl;
	for (int i = 0; i < partical_num; i++) {
		n[i] = 0;//�d�U����R
		for (int j = 0; j < s_stock_index; j++) {

			random = rand() / 32767.0;
			if (random < beta[j]) {
				partical[i][j] = 1;
			}
			else partical[i][j] = 0;//�H����0��1
									/*if (j == 0 || j == 5 || j == 7 || j == 8 || j == 9 || j == 12 || j == 15 || j == 16 || j == 17)
									{
									partical[i][j] = 1;
									}
									else partical[i][j] = 0;*/

			if (partical[i][j] == 1)
			{
				stock_index[i][n[i]] = j;
				//cout << stock_no[stock_index[i][n[i]]] << endl; //�Ѳ��s��
				//cout << stock_index[i][n[i]]  << endl;//��쪺�Ѳ� index
				n[i] = n[i]++;//�X��
			}

		}

	}
}

void single_stock()
{
	int s_tmp = 0;
	for (int i = 0; i < partical_num; i++)
	{
		n[i] = 0;
		for (int s = 0; s < s_stock_index; s++)
		{
			partical[i][s] = 0;
			if (i == s)
			{
				partical[i][s] = 1;
			}
			else partical[i][s] = 0;

			if (partical[i][s] == 1)
			{
				stock_index[i][n[i]] = s;
				//cout << stock_no[stock_index[i][n[i]]] << endl; //�Ѳ��s��
				//cout << stock_index[i][n[i]]  << endl;//��쪺�Ѳ� index
				n[i] = n[i]++;//�X��
			}
		}
	}
}
/*���ɪѲ����-�C�Ӳɤl��줣�P���Ѳ�*/


void standardization()
{
	for (int i = 0; i < partical_num; i++)
	{
		funds_std_total[i] = 0;
		share_money = initial_fund / n[i];//�C����ܫᥭ���C�ɪ����,���n�R!!!!
		all_share_money[i] = share_money;//��C�Ӳɤl�����t����s�_��
		remaind = initial_fund - share_money * n[i];//���զX���t���ѤU����
		for (int j = 0; j < n[i]; j++) {
			all_buy_lots[j] = 0;
			real_all_remain_fund[j] = 0;
			for (int k = 0; k < day; k++) {
				n_fund_standardization[i][j][k] = 0;
				if (k == 0)
				{
					buy_lots = share_money / all_stock[stock_index[i][j]][k];//����R�X��
																			 //buy_papper = share_money / (all_stock[stock_index[i][j]][k] * 1000.0 + all_stock[stock_index[i][j]][k] * 1.425);//�i�R�i��
					all_buy_lots[j] = buy_lots;
					all_remain_fund = share_money - buy_lots * all_stock[stock_index[i][j]][k];
					real_all_remain_fund[j] = all_remain_fund;//��R���U�ѳѾl����s�J�}�C���i��P�_
															  //fee = all_stock[stock_index[i][j]][k] * buy_papper * 1000 * fee_rate;//����O v
					n_fund_standardization[i][j][k] = share_money;
					//n_fund_standardization[i][j][k] = share_money - all_stock[stock_index[i][j]][k] * buy_papper * 1000 * fee_rate;//������� v

				}
				else
				{
					n_fund_standardization[i][j][k] = all_stock[stock_index[i][j]][k] * buy_lots + all_remain_fund;
					/*n_fund_standardization[i][j][k] = all_stock[stock_index[i][j]][k] * buy_papper -
					all_stock[stock_index[i][j]][k] * buy_papper * 1000 * fee_rate - buy_papper * all_stock[stock_index[i][j]][k] * 1000 * tax_rate + all_remain_fund;*/

				}
				/*if (share_money < 0)
				{
				n_fund_standardization[i][j][k] = 0;
				}*/
			}

		}

		for (int k = 0; k < day; k++)
		{
			yi[i][k] = 0;
			//all_total_yi[k] = 0;
			for (int j = 0; j < n[i]; j++)
			{
				yi[i][k] += n_fund_standardization[i][j][k];//yi total
			}
			yi[i][k] = yi[i][k] + remaind;//v
			all_total_yi[k] = yi[i][k];
			funds_std_total[i] += yi[i][k];
		}
	}
}


void test_standardization(int a)//���մ��������p��
{
	test_share_money = 0;
	test_share_money = test_initial_fund / Gbest_n;//�C����ܫᥭ���C�ɪ����,���n�R!!!!
	test_remaind = test_initial_fund - test_share_money * Gbest_n;//���զX���t���ѤU����
	test_funds_std_total = 0;

	for (int v = 0; v < s_stock_index; v++)
	{
		if (final_portfolio[v] != "/0")
		{
			for (int s = 0; s < test_stock_index; s++)
			{
				//cout << test_stock_no[s] << endl;
				if (final_portfolio[v] == test_stock_no[s])
				{
					//cout << s << endl;
					for (int k = 0; k < test_day; k++) {
						//	test_all_stock[s][k] = 0;
						if (k == 0)
						{
							//test_one_of_price = test_all_stock[s][k] * 1000 + test_all_stock[s][k] * 1.425;//��i����
							test_buy_lots = test_share_money / test_all_stock[s][k];//�i�R�i��
							test_all_buy_lots[s] = test_buy_lots;
							test_all_remain_fund = test_share_money - test_buy_lots * test_all_stock[s][k];//�R���U�ѳѾl���
							test_real_all_remain_fund[s] = test_all_remain_fund;//��R���U�ѳѾl����s�J�}�C���i��P�_;
							test_n_fund_standardization[s][k] = test_share_money;//������� 
						}
						else
						{
							test_n_fund_standardization[s][k] = test_all_stock[s][k] * test_buy_lots + test_all_remain_fund;
						}
						if (test_share_money <= 0)
						{
							test_n_fund_standardization[s][k] = 0;
						}
						if (Gbest_max_sp <= 0)
						{
							test_n_fund_standardization[s][k] = 0;
							test_remaind = 0;
						}
					}
				}
			}

		}
	}

	for (int k = 0; k < test_day; k++)
	{
		test_yi[k] = 0;

		for (int v = 0; v < s_stock_index; v++)
		{
			/*if (final_portfolio[v] != 0)
			{*/
			for (int s = 0; s < test_stock_index; s++)
			{
				if (final_portfolio[v] == test_stock_no[s])
				{
					test_yi[k] = test_yi[k] + test_n_fund_standardization[s][k];//yi total
				}
			}
			//}

		}
		if (Gbest_max_sp <= 0)
		{
			test_yi[k] = test_initial_fund;
		}
		test_yi[k] += test_remaind;
		test_all_total_yi[k] = test_yi[k];
		test_all_final_fund = test_yi[test_day - 1];

		if (test_yi[k] > 0)
		{
			real_last_total_std[a][k] = test_yi[k];
		}
		/*if (Gbest_max_sp <= 0)
		{
			test_yi[k] = test_initial_fund;
		}*/
		if (Gbest_max_sp <= 0)
		{
			real_last_total_std[a][k] = test_initial_fund;
		}
		else if (test_yi[k] <= 10)
		{
			real_last_total_std[a][k] = test_initial_fund;
		}

		/*if (a == 30 || a == 31 || a == 32 || a == 33)
		{
			cout << "�`�������:" << fixed << setprecision(15) << test_yi[k] << endl;
			cout << "�L����:" << fixed << setprecision(15) << Gbest_max_sp << endl;
			cout << "�`���մ���X�������:" << fixed << setprecision(15) << real_last_total_std[a][k] << endl;
			system("pause");
		}*/

		test_funds_std_total += test_yi[k];
		all_test_funds_std_total += real_last_total_std[a][k];
	}
}

void all_test_sp_cal()
{
	double all_test_funds_std_standard_deviation_tmp_1;
	double all_test_funds_std_standard_deviation_tmp_2;

	all_test_roi = 0;
	all_test_funds_std_standard_deviation = 0;
	all_test_funds_std_standard_deviation_tmp_1 = 0;
	all_test_funds_std_standard_deviation_tmp_2 = 0;
	all_test_sharpe_ratio_risk = 0;
	all_test_sharpe_ratio = 0;
	all_test_sharpe_ratio_return = 0;
	all_test_average_funds_std = 0;
	all_test_roi = (test_all_final_fund - initial_fund) / initial_fund;
	all_test_average_funds_std = all_test_funds_std_total / total_test_day;
	cout << fixed << setprecision(20) << all_test_funds_std_total << endl;
	for (int a = 0; a < file_num; a++)
	{
		for (int d = 0; d < total_test_day; d++)
		{
			if (real_last_total_std[a][d] != 0)
			{
				all_test_funds_std_standard_deviation_tmp_1 = real_last_total_std[a][d] - all_test_average_funds_std;
				all_test_funds_std_standard_deviation_tmp_1 *= all_test_funds_std_standard_deviation_tmp_1;
				all_test_funds_std_standard_deviation_tmp_2 += all_test_funds_std_standard_deviation_tmp_1;
			}
		}
	}
	all_test_funds_std_standard_deviation_tmp_2 = (all_test_funds_std_standard_deviation_tmp_2 / total_test_day);
	all_test_funds_std_standard_deviation = sqrt(all_test_funds_std_standard_deviation_tmp_2);
	all_test_sharpe_ratio_risk = all_test_funds_std_standard_deviation / all_test_average_funds_std;//�L���ȭ��I
	cout << "����:" << fixed << setprecision(20) << all_test_average_funds_std << endl;
	all_test_sharpe_ratio_return = all_test_roi - risk_free;//�L���ȳ��S
	all_test_sharpe_ratio = all_test_sharpe_ratio_return / all_test_sharpe_ratio_risk;
}


void sp_test_cal()//���մ��L���ȭp��
{

	double test_funds_std_standard_deviation_tmp_1;
	double test_funds_std_standard_deviation_tmp_2;

	test_roi = 0;
	test_funds_std_standard_deviation = 0;
	test_funds_std_standard_deviation_tmp_1 = 0;
	test_funds_std_standard_deviation_tmp_2 = 0;
	test_average_funds_std = 0;
	test_sharpe_ratio_risk = 0;
	test_sharpe_ratio = 0;
	test_sharpe_ratio_return = 0;
	if (Gbest_max_sp > 0)
	{
		test_roi = (test_all_final_fund - test_initial_fund) / test_initial_fund;
		test_average_funds_std = test_funds_std_total / test_day;
		for (int k = 0; k < test_day; k++)
		{
			test_funds_std_standard_deviation_tmp_1 = test_yi[k] - test_average_funds_std;
			test_funds_std_standard_deviation_tmp_1 *= test_funds_std_standard_deviation_tmp_1;
			test_funds_std_standard_deviation_tmp_2 += test_funds_std_standard_deviation_tmp_1;
		}
		test_funds_std_standard_deviation_tmp_2 = (test_funds_std_standard_deviation_tmp_2 / test_day);
		test_funds_std_standard_deviation = sqrt(test_funds_std_standard_deviation_tmp_2);
		test_sharpe_ratio_risk = test_funds_std_standard_deviation / test_average_funds_std;//�L���ȭ��I
		test_sharpe_ratio_return = test_roi - risk_free;//�L���ȳ��S
		test_sharpe_ratio = test_sharpe_ratio_return / test_sharpe_ratio_risk;
	}
}

void sharpe_ratio_cal()//�V�m���L���ȭp��
{
	double funds_std_standard_deviation_tmp_1 = 0;
	double funds_std_standard_deviation_tmp_2 = 0;
	for (int i = 0; i < partical_num; i++)
	{
		roi[i] = 0;
		funds_std_standard_deviation[i] = 0;
		funds_std_standard_deviation_tmp_1 = 0;
		funds_std_standard_deviation_tmp_2 = 0;
		average_funds_std[i] = 0;
		roi[i] = (yi[i][day - 1] - initial_fund) / initial_fund;
		average_funds_std[i] = funds_std_total[i] / day;
		//cout << "�����������" << fixed << setprecision(20) << average_funds_std[i] << endl;
		sharpe_ratio_risk[i] = 0;
		sharpe_ratio[i] = 0;
		sharpe_ratio_return[i] = 0;

		for (int k = 0; k < day; k++)
		{
			funds_std_standard_deviation_tmp_1 = yi[i][k] - average_funds_std[i];
			funds_std_standard_deviation_tmp_1 *= funds_std_standard_deviation_tmp_1;
			funds_std_standard_deviation_tmp_2 += funds_std_standard_deviation_tmp_1;
		}
		funds_std_standard_deviation_tmp_2 = (funds_std_standard_deviation_tmp_2 / day);
		funds_std_standard_deviation[i] = sqrt(funds_std_standard_deviation_tmp_2);
		sharpe_ratio_risk[i] = funds_std_standard_deviation[i] / average_funds_std[i];//�L���ȭ��I
		sharpe_ratio_return[i] = roi[i] - risk_free;//�L���ȳ��S
		sharpe_ratio[i] = sharpe_ratio_return[i] / sharpe_ratio_risk[i];
		//cout << "�L����:" << fixed << setprecision(20) << sharpe_ratio[i] << endl;
	}

}


void single_compare()
{

	for (int i = 0; i < partical_num; i++)
	{
		single_trend_ratio[i] = all_trend_ratio[i];
	}
	sort(single_trend_ratio, single_trend_ratio + partical_num, greater<double>());
}
/*�����ͶխȥѤj��p�Ƨ�*/

void sharpe_ratio_compare(int j)//�L���Ⱦɤޤ��
{
	max_sharpe_ratio = sharpe_ratio[0];
	max_sharpe_ratio_tmp = 0;
	all_max_sharpe_ratio;
	for (int i = 0; i < partical_num; i++)
	{
		if (max_sharpe_ratio < sharpe_ratio[i])
		{
			max_sharpe_ratio = sharpe_ratio[i];
			max_sharpe_ratio_tmp = i;
		}
	}
	min_sharpe_ratio = max_sharpe_ratio;
	for (int i = 0; i < partical_num; i++)
	{
		if (min_sharpe_ratio > sharpe_ratio[i])
		{
			min_sharpe_ratio = sharpe_ratio[i];
			min_sharpe_ratio_tmp = i;
		}
	}//��Best&Worst

	if (max_sharpe_ratio > all_max_sharpe_ratio)
	{
		all_max_sharpe_ratio = max_sharpe_ratio;
		//cout << fixed << setprecision(20) << all_max_sharpe_ratio << endl;
		for (int k = 0; k < s_stock_index; k++)
		{
			all_max_solution[k] = partical[max_sharpe_ratio_tmp][k];
			//cout << all_max_solution[k];
		}
	}//Gbest

	if (all_max_sharpe_ratio <= 0)
	{
		for (int k = 0; k < s_stock_index; k++)
		{
			all_max_solution[k] = 0;
			all_max_sharpe_ratio = 0;
		}
	}

	for (int k = 0; k < s_stock_index; k++) {
		if (all_max_solution[k] == 0 && partical[min_sharpe_ratio_tmp][k] == 1)
		{
			if (beta[k] > 0.5)
			{
				beta[k] = 1 - beta[k];
				beta[k] = beta[k] - theta;
			}

			else if (beta[k] <= 0.5)
			{
				beta[k] = beta[k] - theta;
			}
		}
		if (all_max_solution[k] == 1 && partical[min_sharpe_ratio_tmp][k] == 0)
		{
			if (beta[k] < 0.5)
			{
				beta[k] = 1 - beta[k];
				beta[k] = beta[k] + theta;
			}
			else if (beta[k] >= 0.5)
			{
				beta[k] = beta[k] + theta;
			}
		}
	}
	final_max_tmp[j] = max_sharpe_ratio_tmp;
}


void compare()
{
	max_fitness = all_trend_ratio[0];//�p�G�o��]��0,��쪺���@�w�O��N�ɤl���̤j�ȡC(�p�G��N�ɤl���O�t��)
	max_fitness_tmp = 0;
	for (int i = 0; i < partical_num; i++)
	{
		if (max_fitness < all_trend_ratio[i])
		{
			max_fitness = all_trend_ratio[i];
			max_fitness_tmp = i;
		}
	}
	min_fitness = max_fitness;

	for (int i = 0; i < partical_num; i++)
	{

		if (min_fitness > all_trend_ratio[i])
		{
			min_fitness = all_trend_ratio[i];
			min_fitness_tmp = i;
		}
	}//��Best&Worst

	if (max_fitness > all_max)
	{
		all_max = max_fitness;
		for (int k = 0; k < s_stock_index; k++)
		{
			all_max_solution[k] = partical[max_fitness_tmp][k];
		}
	}//Gbest

	if (all_max <= 0)
	{
		for (int k = 0; k < s_stock_index; k++)
		{
			all_max_solution[k] = 0;
		}
	}

	for (int k = 0; k < s_stock_index; k++) {
		if (all_max_solution[k] == 0 && partical[min_fitness_tmp][k] == 1)
		{
			if (beta[k] > 0.5)
			{
				beta[k] = 1 - beta[k];
				beta[k] = beta[k] - theta;
			}

			else if (beta[k] <= 0.5)
			{
				beta[k] = beta[k] - theta;
			}
		}
		if (all_max_solution[k] == 1 && partical[min_fitness_tmp][k] == 0)
		{
			if (beta[k] < 0.5)
			{
				beta[k] = 1 - beta[k];
				beta[k] = beta[k] + theta;
			}
			else if (beta[k] >= 0.5)
			{
				beta[k] = beta[k] + theta;
			}
		}
	}
}

void experiment_sp_compare()/*50������Sharpe ratio���,�ç�X�̦n��Sharpe ratio�������*/
{
	Gbest_max_sp = all_sharpe_ratio_max_tmp[0];
	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max_sp <= all_sharpe_ratio_max_tmp[j])
		{
			Gbest_max_sp = all_sharpe_ratio_max_tmp[j];
		}//��50�����窺Gbest,�p�G�u���@������i����
	}

	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max_sp == all_sharpe_ratio_max_tmp[j])
		{
			best_experimrentime = j + 1;//��̨θѹ��禸��
			break;
		}
	}
	//cout << fixed << setprecision(20) << Gbest_max_sp << endl;
}


void experiment_compre() /*50������Gbest���,�ç�XGbest�������*/
{
	Gbest_max = all_max_tmp[0];
	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max <= all_max_tmp[j])
		{
			Gbest_max = all_max_tmp[j];
		}//��50�����窺Gbest,�p�G�u���@������i����
	}

	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max == all_max_tmp[j])
		{
			best_experimrentime = j + 1;//��̨θѹ��禸��
			break;
		}
	}
}

void Gbest_sp_num_find()//��̦nSP�b���礤�X�{������
{
	Gbest_num = 0;
	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max_sp == all_sharpe_ratio_max_tmp[j])
		{
			Gbest_num += 1;
		}
		//cout << all_sharpe_ratio_max_tmp[j] << endl;
	}
}

void Gbest_num_find()//��Gbest����禸�Ƥ��X�{������
{
	Gbest_num = 0;
	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max == all_max_tmp[j])
		{
			Gbest_num += 1;
		}
	}

}

void sp_generation_compare()//�L���ȥ@�N�����
{
	for (int j = 0; j < experiment_time; j++)
	{
		for (int t = 0; t < generation; t++)
		{
			for (int i = 0; i < partical_num; i++)
			{
				if (Gbest_max_sp == real_all_sharpe_ratio[j][t][i])
				{
					best_generation = t + 1;//�̨θѥ@�N��
					Gbest_daily_risk = all_sp_risk[j][t][i];//�̨θѭ��I
					Gbest_expect_retutn = all_sp_return[j][t][i];//�̨θѹw�����S
					Gbest_n = final_n[j][t][i];
					Gbest_share_money = compare_share_money[j][t][i];
					Gbest_i = i;
					for (int k = 0; k < Gbest_n; k++)
					{
						Gbest_all_remain_fund[k] = 0;
						Gbest_buy_lots[k] = compare_buy_lots[j][i][k];//�i�R�i��
						Gbest_all_remain_fund[k] = compare_remain_fund[j][k];
						for (int d = 0; d < day; d++)
						{
							Gbest_n_fund_standardization[k][d] = all_n_fund_standardization[j][k][d];
						}
					}
					for (int d = 0; d < day; d++)
					{
						real_total_yi[d] = compare_total_yi[j][d];
						Gbest_yi = real_total_yi[day - 1];
					}
					return;
				}
			}
		}
	}
}


void generation_compare()
{
	best_generation = 0;
	for (int j = 0; j < experiment_time; j++)
	{
		for (int t = 0; t < generation; t++)
		{
			for (int i = 0; i < partical_num; i++)
			{
				//if (Gbest_max == real_all_trend_ratio[j][t][i])
				{
					best_generation = t + 1;//�̨θѥ@�N��
					Gbest_daily_risk = daily_risk[j][t][i];//�̨θѭ��I
					Gbest_expect_retutn = expect_m[j][t][i];//�̨θѹw�����S
					Gbest_n = final_n[j][t][i];
					Gbest_share_money = compare_share_money[j][t][i];
					Gbest_i = i;
					for (int k = 0; k < Gbest_n; k++)
					{
						Gbest_all_remain_fund[k] = 0;
						Gbest_buy_lots[k] = compare_buy_lots[j][i][k];//�i�R�i��
						Gbest_all_remain_fund[k] = compare_remain_fund[j][k];
						for (int d = 0; d < day; d++)
						{
							Gbest_n_fund_standardization[k][d] = all_n_fund_standardization[j][k][d];
						}
					}
					for (int d = 0; d < day; d++)
					{
						real_total_yi[d] = compare_total_yi[j][d];
						Gbest_yi = real_total_yi[day - 1];
					}
					return;
				}
			}
		}
	}
}

void Gbest_sp_stock_selection()//�O�L���ȰV�m�X���̦n���զX
{
	for (int j = 0; j < experiment_time; j++)
	{

		/*for (int i = 0; i < partical_num; i++)
		{*/
		if (j == best_experimrentime - 1)
		{
			for (int s = 0; s < s_stock_index; s++)
			{
				final_portfolio[s] = "\0";
				//cout << real_partical[j][i][s] << endl;

				if (real_partical[best_experimrentime - 1][Gbest_i][s] == 1)
				{
					final_portfolio[s] = stock_no[s];//Gbest���զX��
					train_stock_index[s] = s;
					//cout << final_portfolio[s] << endl;
				}
			}
			return;
		}
		//}


	}
}

void sp_out_file(int a)
{
	if (Gbest_max_sp > 0)
	{
		string ouput_file = "Larry_result_" + HH_train50[a].substr(0, HH_train50[a].length());//��X�ɮצW��
		output_file.open(ouput_file, ios::app);//�ɮ׿�X
		output_file << "�N��" << "," << generation << endl;
		output_file << "�ɤl��" << "," << partical_num << endl;
		output_file << "���ਤ�פW��" << "," << theta << endl;
		output_file << "���ਤ�פU��" << "," << theta << endl;
		output_file << "���ਤ��" << "," << theta << endl;
		output_file << "���禸��" << "," << experiment_time << endl << endl;
		output_file << "��l���" << "," << initial_fund << endl;
		output_file << "�̫���" << "," << fixed << setprecision(15) << Gbest_yi << endl;
		output_file << "�u����S" << "," << fixed << setprecision(15) << Gbest_yi - initial_fund << endl << endl;
		output_file << "�L���ȳ��S" << "," << fixed << setprecision(15) << Gbest_expect_retutn << endl;
		output_file << "�L���ȭ��I" << "," << fixed << setprecision(15) << Gbest_daily_risk << endl;
		output_file << "�L����" << "," << fixed << setprecision(10) << Gbest_max_sp << endl;
		output_file << "���̨θѥ@�N" << "," << best_generation << endl;
		output_file << "���̨θѹ���#" << "," << best_experimrentime << endl;
		output_file << "���̨θѦ���" << "," << Gbest_num << endl << endl;
		output_file << "���զX�ɼ�" << "," << Gbest_n << endl;
		for (int s = 0; s < s_stock_index; s++)
		{
			if (final_portfolio[s] != "\0")
			{
				output_file << final_portfolio[s] << "(" << s << ")" << ",";
			}

		}
		output_file << endl;
		output_file << "Stock#" << ",";
		for (int s = 0; s < s_stock_index; s++)
		{
			if (final_portfolio[s] != "\0")
			{
				output_file << final_portfolio[s] << "(" << s << ")" << ",";
			}
		}
		output_file << endl;
		output_file << "�Ѽ�" << ",";
		for (int k = 0; k < Gbest_n; k++)
		{
			output_file << Gbest_buy_lots[k] << ",";
		}
		output_file << endl;
		output_file << "���t���" << ",";
		for (int k = 0; k < Gbest_n; k++)
		{
			output_file << Gbest_share_money << ",";
		}
		output_file << endl;
		output_file << "�Ѿl���" << ",";
		for (int k = 0; k < Gbest_n; k++)
		{
			output_file << Gbest_all_remain_fund[k] << ",";
		}
		output_file << endl;
		for (int d = 0; d < day; d++)
		{
			output_file << "FS(" << d + 1 << ")" << ",";
			for (int k = 0; k < Gbest_n; k++)
			{
				output_file << fixed << setprecision(15) << Gbest_n_fund_standardization[k][d] << ",";
			}
			output_file << fixed << setprecision(15) << real_total_yi[d] << "," << endl;

		}
		output_file.close();
	}
}

void sp_test_out_file(int a)
{
	if (Gbest_max_sp > 0)
	{
		string ouput_file = "Larry_result_" + HH_test50[a].substr(0, HH_test50[a].length());//��X�ɮצW��
		output_file.open(ouput_file, ios::app);//�ɮ׿�X
		output_file << "�N��" << "," << generation << endl;//v
		output_file << "�ɤl��" << "," << partical_num << endl;//v
		output_file << "���ਤ��" << "," << theta << endl;//v
		output_file << "���禸��" << "," << experiment_time << endl << endl;//v
		output_file << "��l���" << "," << test_initial_fund << endl;//v
		output_file << "�̫���" << "," << fixed << setprecision(15) << test_all_final_fund << endl;
		output_file << "�u����S" << "," << fixed << setprecision(15) << test_all_final_fund - test_initial_fund << endl << endl;
		output_file << "�w�����S" << "," << fixed << setprecision(15) << test_sharpe_ratio_return << endl;//v
		output_file << "���I" << "," << fixed << setprecision(15) << test_sharpe_ratio_risk << endl;//v
		output_file << "�L����" << "," << fixed << setprecision(11) << test_sharpe_ratio << endl;//v
		output_file << endl;
		output_file << "���զX�ɼ�" << "," << Gbest_n << endl;
		for (int s = 0; s < test_stock_index; s++)
		{
			for (int v = 0; v < s_stock_index; v++)
			{
				/*if (final_portfolio[s] != 0)
				{*/
				if (final_portfolio[v] == test_stock_no[s])
				{
					output_file << test_stock_no[s] << "(" << s << ")" << ",";
				}
				//}
			}
		}
		output_file << endl;
		output_file << "Stock#" << ",";
		for (int s = 0; s < test_stock_index; s++)
		{
			for (int v = 0; v < s_stock_index; v++)
			{
				/*if (final_portfolio[s] != 0)
				{*/
				if (final_portfolio[v] == test_stock_no[s])
				{
					output_file << test_stock_no[s] << "(" << s << ")" << ",";
				}
				//}
			}
		}
		output_file << endl;
		output_file << "�Ѽ�" << ",";

		for (int s = 0; s < test_stock_index; s++)
		{
			for (int v = 0; v < s_stock_index; v++)
			{
				/*if (final_portfolio[s] != 0)
				{*/
				if (final_portfolio[v] == test_stock_no[s])
				{
					output_file << test_all_buy_lots[s] << ",";

				}
				//}
			}
		}
		output_file << endl;
		output_file << "���t���" << ",";
		for (int k = 0; k < Gbest_n; k++)
		{
			output_file << test_share_money << ",";
		}
		output_file << endl;
		output_file << "�Ѿl���" << ",";
		for (int s = 0; s < test_stock_index; s++)
		{
			for (int v = 0; v < s_stock_index; v++)
			{
				/*if (final_portfolio[s] != 0)
				{*/
				if (final_portfolio[v] == test_stock_no[s])
				{
					output_file << test_real_all_remain_fund[s] << ",";
				}
				//}
			}
		}
		output_file << endl;
		for (int d = 0; d < test_day; d++)
		{
			output_file << "FS(" << d + 1 << ")" << ",";
			for (int s = 0; s < test_stock_index; s++)
			{
				for (int v = 0; v < s_stock_index; v++)
				{
					/*if (final_portfolio[s] != 0)
					{*/
					if (final_portfolio[v] == test_stock_no[s])
					{
						output_file << fixed << setprecision(15) << test_n_fund_standardization[s][d] << ",";
					}
					//}
				}
			}
			output_file << fixed << setprecision(15) << test_all_total_yi[d] << "," << endl;
		}
		output_file.close();
	}
}

void all_testperiod_final_result()
{
	string ouput_file = "Larry_50_SP_H#_total_test_result.csv";//��X�ɮצW��
	output_file.open(ouput_file, ios::app);//�ɮ׿�X
	output_file << "���մ��϶�" << "," << "test_2016_Q1-Q2(2015 Q1).csv - test_2019_Q3-Q4(2018 Q1).csv" << endl;
	output_file << "�@�N��" << "," << generation << endl;
	output_file << "���ਤ��" << "," << theta << endl;
	output_file << "�ɤl��" << "," << partical_num << endl;
	output_file << "���禸��" << "," << experiment_time << endl;
	output_file << "��l���" << "," << initial_fund << endl;
	output_file << "�u����S" << "," << fixed << setprecision(15) << test_all_final_fund - initial_fund << endl << endl;
	output_file << "�w�����S" << "," << fixed << setprecision(15) << all_test_sharpe_ratio_return << endl;
	output_file << "���I" << "," << fixed << setprecision(15) << all_test_sharpe_ratio_risk << endl;
	output_file << "�L����" << "," << fixed << setprecision(10) << all_test_sharpe_ratio << endl;
	output_file << "�`�Ѽ�" << "," << total_test_day << endl;
	output_file << "�Ѽ�" << "," << "�`�������" << endl;
	for (int a = 0; a < file_num; a++)
	{
		for (int d = 0; d < total_test_day; d++)
		{
			if (real_last_total_std[a][d] != 0)
			{
				day_count_result++;
				output_file << "FS(" << day_count_result << ")" << ",";
				output_file << real_last_total_std[a][d] << endl;

			}
		}
	}

	output_file.close();
}

void all_sp_train_prtiod_result(int a)//�L���ȩҦ��V�m�����G��X
{
	string ouput_file = "Larry_50_H#_train_Gbest_10000_10_50_0.0004.csv";//��X�ɮצW��
	output_file.open(ouput_file, ios::app);

	if (all_file_best_sp[a] > 0)
	{
		output_file << a + 1 << "," << all_file_gbest_num[a] << ",";
		for (int s = 0; s < s_stock_index; s++)
		{
			if (all_file_gbest_portfolio[a][s] != "\0")
			{
				output_file << all_file_gbest_portfolio[a][s] << "(" << s << ") " << " ";
			}
		}
		output_file << ",";
		output_file << "�L����" << "," << fixed << setprecision(20) << all_file_best_sp[a] << ",";
		output_file << "�w�����S" << "," << fixed << setprecision(20) << all_file_gbest_return[a] << ",";
		output_file << "���I" << "," << fixed << setprecision(20) << all_file_gbest_risk[a] << ",";
		output_file << "�̨θѹ���#" << "," << all_file_gbest_experiment[a] << ",";
		output_file << "�̨θѥ@�N#" << "," << all_file_gbest_generation[a] << ",";
		output_file << "�̨θѥX�{����" << "," << all_file_gbest_appear[a];
		output_file << endl;
	}
	output_file.close();
}

void sp_testing_period(int a)
{

	string ouput_file = "Larry_50_H#_SP_test_Gbest_10000_10_50_0.0004.csv";//��X�ɮצW��
	output_file.open(ouput_file, ios::app);


	output_file << a + 1 << "," << all_file_gbest_num[a] << ",";
	for (int s = 0; s < s_stock_index; s++)
	{
		if (all_file_test_portfolio[a][s] != "\0")
		{
			output_file << all_file_test_portfolio[a][s] << "(" << s << ") " << " ";
		}
	}
	output_file << ",";
	output_file << "�L����" << "," << fixed << setprecision(20) << final_test_period_sharpe_ratio[a] << ",";
	output_file << "�w�����S" << "," << fixed << setprecision(20) << final_test_period_sharpe_return[a] << ",";
	output_file << "���I" << "," << fixed << setprecision(20) << final_test_period_sharpe_ratio_risk[a] << ",";
	output_file << endl;
	output_file.close();
}


void single_output(int a)
{
	string ouput_file = "Larry_US50_Q2Q_train_single_result.csv";//��X�ɮצW��
	output_file.open(ouput_file, ios::app);
	output_file << "File" << "," << "Rank" << "," << "Stock" << endl;
	for (int i = 0; i < partical_num; i++)
	{
		output_file << a + 1 << ",";
		output_file << i + 1 << ",";
		for (int u = 0; u < partical_num; u++)
		{
			if (all_single_trend_ratio[a][i] == all_all_trend_ratio[a][u])
			{
				if (all_single_trend_ratio[a][i] != 0)
				{
					output_file << all_stock_no[a][u] << "," << "�Ͷխ�" << "," << fixed << setprecision(15) << all_single_trend_ratio[a][i];
					output_file << "," << "�w�����S" << "," << fixed << setprecision(15) << all_single_m[a][u] << "," << "���I" << "," << fixed << setprecision(15) << all_single_risk[a][u];
				}
			}
		}
		output_file << endl;
	}
	output_file.close();
}
int main()
{
	srand(114);
	for (int a = 0; a < file_num; a++)
	{
		index = 0;
		day = 0;
		read_file(a);
		for (int j = 0; j < experiment_time; j++)
		{
			//index = 0;
			//day = 0;
			all_max = 0;
			all_max_sharpe_ratio = -999999999.0;
			initial();
			for (int t = 0; t < generation; t++)
			{
				measure();
				//single_stock();
				standardization();
				//single_compare();//�����ͶխȱƧ�
				sharpe_ratio_cal();//�L���Ⱦɤ�
				sharpe_ratio_compare(j);//�L���Ⱦɤޤ��
										//compare();//�ͶխȾɤޤ��
				for (int i = 0; i < partical_num; i++)
				{
					all_stock_no[a][i] = '/0';
					//real_all_trend_ratio[j][t][i] = all_trend_ratio[i];//�Ͷխ�
					daily_risk[j][t][i] = risk[i];
					expect_m[j][t][i] = m[i];
					final_n[j][t][i] = n[i];
					compare_share_money[j][t][i] = all_share_money[i];

					all_all_trend_ratio[a][i] = all_trend_ratio[i];
					all_single_trend_ratio[a][i] = single_trend_ratio[i];
					all_stock_no[a][i] = stock_no[i];
					all_single_m[a][i] = m[i];
					all_single_risk[a][i] = risk[i];
					/*�Ͷխ�*/

					real_all_sharpe_ratio[j][t][i] = sharpe_ratio[i];//�L����
					all_sp_risk[j][t][i] = sharpe_ratio_risk[i];
					all_sp_return[j][t][i] = sharpe_ratio_return[i];
					/*�L����*/
					for (int s = 0; s < s_stock_index; s++)
					{
						real_partical[j][i][s] = partical[i][s];//Think
																//cout << real_partical[j][i][s];

					}
					//cout << endl;

					for (int k = 0; k < n[i]; k++)
					{
						compare_buy_lots[j][i][k] = all_buy_lots[k];
						compare_remain_fund[j][k] = real_all_remain_fund[k];
						for (int d = 0; d < day; d++)
						{
							all_n_fund_standardization[j][k][d] = n_fund_standardization[i][k][d];
							compare_total_yi[j][d] = all_total_yi[d];

						}
					}

				}
			}
			all_max_tmp[j] = all_max;//�N�C�������쪺Gbest��J�}�C��	
			all_sharpe_ratio_max_tmp[j] = all_max_sharpe_ratio;
			//cout << all_sharpe_ratio_max_tmp[j] << endl;
			//cout << fixed << setprecision(20) << all_sharpe_ratio_max_tmp[j] << endl;
		}
		//experiment_compre();
		experiment_sp_compare();//�����̦n���L����
								//Gbest_num_find();
		Gbest_sp_num_find();//����礤�̦n�L���ȥX�{������
							//generation_compare();
		sp_generation_compare();//�L���ȥ@�N�Ƥ��
		Gbest_sp_stock_selection();//�O�L���ȰV�m�X���̦n���զX
								   //out_file(a);
		sp_out_file(a);//�L���ȿ�X
		test_index = 0;
		test_read_file(a);//���մ�Ū��
		if (a == 0)
		{
			test_initial_fund = initial_fund;//�p�G�O�Ĥ@�Ӵ��մ��ɮ�,�h��l�����10000000
		}
		if (test_all_final_fund <= 0)
		{
			test_initial_fund = test_initial_fund;
		}
		else if (a != 0)
		{
			test_initial_fund = test_all_final_fund;//�ĤG�Ӵ��մ��ɮ׶}�l,��l������W�@�϶��̫���

		}
		test_standardization(a);
		//single_output(a);//���ɧ��զX��X
		//test_fitness(a);//�Ͷխȴ��մ�
		sp_test_cal();
		//all_test_return();//�`����մ��w�����S�p��
		if (Gbest_max_sp > 0)
		{
			final_test_period_sharpe_ratio[a] = test_sharpe_ratio;
			final_test_period_sharpe_ratio_risk[a] = test_sharpe_ratio_risk;
			final_test_period_sharpe_return[a] = test_sharpe_ratio_return;
		}

		sp_test_out_file(a);//�Ͷխȴ��մ��ɮ׿�X

		all_file_gbest_risk[a] = Gbest_daily_risk;
		all_file_gbest_return[a] = Gbest_expect_retutn;
		all_file_gbest_num[a] = Gbest_n;
		all_file_gbest_generation[a] = best_generation;
		all_file_gbest_experiment[a] = best_experimrentime;
		all_file_gbest_appear[a] = Gbest_num;
		all_gbest_trend_ratio[a] = Gbest_max;
		all_file_best_sp[a] = Gbest_max_sp;


		for (int s = 0; s < s_stock_index; s++)
		{
			if (final_portfolio[s] != "/0")
			{
				all_file_gbest_portfolio[a][s] = final_portfolio[s];
			}
			for (int v = 0; v < test_stock_index; v++)
			{
				if (final_portfolio[s] != "/0" && test_stock_no[v] == final_portfolio[s])
				{
					all_file_test_portfolio[a][s] = test_stock_no[s];
				}
			}
		}
		all_sp_train_prtiod_result(a);//�L���ȦU�V�m�����G��X
									  //all_train_prtiod_result(a);
		if (Gbest_max_sp > 0)
		{
			sp_testing_period(a);//���մ��U�϶���X
		}
	}
	all_test_sp_cal();
	//all_test_risk();//�`����մ����I�p��
	all_testperiod_final_result();//�`����մ����G��X
	cout << endl << (double)clock() / CLOCKS_PER_SEC << "S" << endl;
	system("pause");
	return 0;
}