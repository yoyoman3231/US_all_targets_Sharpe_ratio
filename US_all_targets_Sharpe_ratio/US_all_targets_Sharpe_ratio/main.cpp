/*美股市值前20大、美股市值前50大、道瓊30*/
/*跑投資組合時,記得把單檔關掉*/
/*這邊是用夏普值導引*/
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
double all_stock[10000][10000]; //所有股票
double test_all_stock[100][400];
string stock_no[50]; //股票編號
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
//int profolio[50];//投資組合
//initial

int stock_index[10][50];//記錄每顆粒子(10)所選到的投資組合(50)
						//choose

int train_stock_index[50];
double initial_fund = 10000000; //初始資金
double test_initial_fund;
double remaind;//剩餘資金
double test_remaind;
double all_remain_fund;
double test_all_remain_fund;
double fund_standardization; //資金水位
double fee; //手續費
double test_fee;
double total_fee[50000];
double one_fund_standardization[50][2500];
double n_fund_standardization[100][50][2500];//各檔資金水位
double test_n_fund_standardization[50][300];//測試期資金水位
double partical_fund_standardization[100][2500];//投資組合資金水位
double risk[10000]; //每日風險
double test_risk;//訓練期每日風險
double final_test_risk;
double m[10000]; //預期報酬
double test_m;
int share_money;//每檔分配的錢
int test_share_money;
double one_of_price; //每張的錢
double test_one_of_price;
double daily_risk[50][10000][10];//每次實驗每代每日風險
double expect_m[50][10000][10];//每次實驗每代預期報酬
double Gbest_daily_risk;//最佳解每日風險
double Gbest_expect_retutn;//最佳解預期報酬

int buy_lots;//可買的張數
int test_buy_lots;
double yi[10000][10000];//第i天真實資金水位
double test_yi[1000];
double all_final_yi[10000];//每一個粒子最後一天的yi
						   //standardization

double m1;
int m2;
double all_standardization[2500];
double Yi[100][300];//一次回歸趨勢線
double test_Yi[300];
double r1;
double trend_ratio;//趨勢值
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
int n[partical_num];//算選的投資組合有幾個

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
int Gbest_num;//Gbest的出現次數
int final_n[experiment_time][generation][partical_num];//存最佳解檔數
int Gbest_n;//Gbest選到的檔數
int Gbest_i;
int selection_stock_no[partical_num][50];
int real_partical[50][partical_num][50];
string final_portfolio[50];
int all_buy_lots[50];//存可買張數的陣列
int last_test_all_buy_paper[50];
int test_all_buy_lots[50];
int all_share_money[partical_num];//存分配資金的陣列
int test_all_share_money[partical_num];
int compare_share_money[experiment_time][generation][partical_num];//存每次實驗每個世代每個粒子的分配資金陣列
int compare_buy_lots[50][partical_num][50];//存每個實驗中的組合股票可買張數
int Gbest_share_money;
int Gbest_buy_lots[50];//Gbest組合中股票可買的張數
double real_all_remain_fund[50];
double test_real_all_remain_fund[50];
double compare_remain_fund[50][50];
double Gbest_all_remain_fund[50];//Gbest的買完各股剩餘資金
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
double test_total_all_period_m;//測試期總體預期報酬
double test_all_period_Yi[10000];
double test_all_period_risk;
double test_all_period_trend_ratio;
double test_all_period_m1;
int test_all_period_m2;
double last_total_std[10000];//存所有測試期總資金水位
double last_total_Yi[10000];//計算總體測試期預期資金水位
double real_last_total_std[200][10000];//存所有測試期總資金水位
int day_count;
double all_test_m;
double final_all_test_m;//總體測試期最終預期報酬
double final_test_m1;
double final_test_m2;
double final_test_r1;
int day_count_risk;//總體測試期計算風險天數counter
int day_count_result;//總體測試期輸出結果天數counter

double all_file_gbest_risk[200];//訓練期各區間風險
double all_file_gbest_return[200];//訓練期各區間預期報酬
double all_file_test_return[200];//測試期個區間預期報酬
double all_file_test_risk[200];//測試期各區間風險

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
/*美股市值前12大*/
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
/*美股市值前20大*/

string BAC[] = { "BAC_2012.csv",  "BAC_2013.csv", "BAC_2014.csv", "BAC_2015.csv", "BAC_2016.csv", "BAC_2017.csv", "BAC_2018.csv", "BAC_2019.csv" };
string CSCO[] = { "CSCO_2012.csv", "CSCO_2013.csv", "CSCO_2014.csv", "CSCO_2015.csv", "CSCO_2016.csv", "CSCO_2017.csv", "CSCO_2018.csv", "CSCO_2019.csv" };
string INTC[] = { "INTC_2012.csv", "INTC_2013.csv", "INTC_2014.csv", "INTC_2015.csv", "INTC_2016.csv", "INTC_2017.csv", "INTC_2018.csv", "INTC_2019.csv" };
string VZ[] = { "VZ_2012.csv", "VZ_2013.csv", "VZ_2014.csv", "VZ_2015.csv", "VZ_2016.csv", "VZ_2017.csv", "VZ_2018.csv", "VZ_2019.csv" };
string B_all_US_20[] = { "B_20_2012.csv", "B_20_2013.csv", "B_20_2014.csv", "B_20_2015.csv", "B_20_2016.csv", "B_20_2017.csv", "B_20_2018.csv", "B_20_2019.csv" };
string LG_all_US_20[] = { "LG_20_2012.csv", "LG_20_2013.csv", "LG_20_2014.csv", "LG_20_2015.csv", "LG_20_2016.csv", "LG_20_2017.csv", "LG_20_2018.csv", "LG_20_2019.csv" };
/*確認過後的美股市值前20大*/

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
/*市值前20大訓練期*/

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
/*市值前20大測試期*/

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
/*道瓊30訓練期*/

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
/*道瓊30測試期*/

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
/*市值前50大訓練期*/

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
/*市值前50大測試期*/

double all_single_trend_ratio[file_num][partical_num];//每個區間排序後的單檔趨勢值
double all_all_trend_ratio[file_num][partical_num];//未排序後各區間單檔趨勢值
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


double sharpe_ratio[10];//夏普值
double sharpe_ratio_risk[10];//夏普值風險
double sharpe_ratio_return[10];//夏普值報酬
double risk_free = 0.0087;//台股無風險利率
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
double test_sharpe_ratio;//夏普值
double test_sharpe_ratio_risk;//夏普值風險
double test_sharpe_ratio_return;//夏普值報酬
double all_test_sharpe_ratio;//夏普值
double all_test_sharpe_ratio_risk;//夏普值風險
double all_test_sharpe_ratio_return;//夏普值報酬
double all_test_funds_std_standard_deviation;
double all_test_average_funds_std;
/*夏普值宣告*/

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
				stock_no[s_stock_index] = num; //編號
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
				price >> all_stock[s_stock_index][index - 1];//股價
				s_stock_index++;
			}
			index++;
		}
	}
	input_file.close();
	day = index - 1;
	//cout << day;
}//讀檔

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
				test_num >> test_stock_no[test_stock_index];//編號
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
				test_price >> test_all_stock[test_stock_index][test_index - 1];//股價
				test_stock_index++;
			}
			test_index++;
		}
	}
	test_input_file.close();
	test_day = test_index - 1;
	total_test_day += test_day;
}//讀檔

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
		n[i] = 0;//千萬不能刪
		for (int j = 0; j < s_stock_index; j++) {

			random = rand() / 32767.0;
			if (random < beta[j]) {
				partical[i][j] = 1;
			}
			else partical[i][j] = 0;//隨機給0或1
									/*if (j == 0 || j == 5 || j == 7 || j == 8 || j == 9 || j == 12 || j == 15 || j == 16 || j == 17)
									{
									partical[i][j] = 1;
									}
									else partical[i][j] = 0;*/

			if (partical[i][j] == 1)
			{
				stock_index[i][n[i]] = j;
				//cout << stock_no[stock_index[i][n[i]]] << endl; //股票編號
				//cout << stock_index[i][n[i]]  << endl;//選到的股票 index
				n[i] = n[i]++;//幾檔
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
				//cout << stock_no[stock_index[i][n[i]]] << endl; //股票編號
				//cout << stock_index[i][n[i]]  << endl;//選到的股票 index
				n[i] = n[i]++;//幾檔
			}
		}
	}
}
/*單檔股票選擇-每個粒子選到不同的股票*/


void standardization()
{
	for (int i = 0; i < partical_num; i++)
	{
		funds_std_total[i] = 0;
		share_money = initial_fund / n[i];//每次選擇後平均每檔的資金,不要刪!!!!
		all_share_money[i] = share_money;//把每個粒子的分配資金存起來
		remaind = initial_fund - share_money * n[i];//投資組合分配完剩下的錢
		for (int j = 0; j < n[i]; j++) {
			all_buy_lots[j] = 0;
			real_all_remain_fund[j] = 0;
			for (int k = 0; k < day; k++) {
				n_fund_standardization[i][j][k] = 0;
				if (k == 0)
				{
					buy_lots = share_money / all_stock[stock_index[i][j]][k];//能夠買幾股
																			 //buy_papper = share_money / (all_stock[stock_index[i][j]][k] * 1000.0 + all_stock[stock_index[i][j]][k] * 1.425);//可買張數
					all_buy_lots[j] = buy_lots;
					all_remain_fund = share_money - buy_lots * all_stock[stock_index[i][j]][k];
					real_all_remain_fund[j] = all_remain_fund;//把買完各股剩餘資金存入陣列中進行判斷
															  //fee = all_stock[stock_index[i][j]][k] * buy_papper * 1000 * fee_rate;//手續費 v
					n_fund_standardization[i][j][k] = share_money;
					//n_fund_standardization[i][j][k] = share_money - all_stock[stock_index[i][j]][k] * buy_papper * 1000 * fee_rate;//資金水位 v

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


void test_standardization(int a)//測試期資金水位計算
{
	test_share_money = 0;
	test_share_money = test_initial_fund / Gbest_n;//每次選擇後平均每檔的資金,不要刪!!!!
	test_remaind = test_initial_fund - test_share_money * Gbest_n;//投資組合分配完剩下的錢
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
							//test_one_of_price = test_all_stock[s][k] * 1000 + test_all_stock[s][k] * 1.425;//單張價格
							test_buy_lots = test_share_money / test_all_stock[s][k];//可買張數
							test_all_buy_lots[s] = test_buy_lots;
							test_all_remain_fund = test_share_money - test_buy_lots * test_all_stock[s][k];//買完各股剩餘資金
							test_real_all_remain_fund[s] = test_all_remain_fund;//把買完各股剩餘資金存入陣列中進行判斷;
							test_n_fund_standardization[s][k] = test_share_money;//資金水位 
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
			cout << "總資金水位:" << fixed << setprecision(15) << test_yi[k] << endl;
			cout << "夏普值:" << fixed << setprecision(15) << Gbest_max_sp << endl;
			cout << "總測試期輸出資金水位:" << fixed << setprecision(15) << real_last_total_std[a][k] << endl;
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
	all_test_sharpe_ratio_risk = all_test_funds_std_standard_deviation / all_test_average_funds_std;//夏普值風險
	cout << "平均:" << fixed << setprecision(20) << all_test_average_funds_std << endl;
	all_test_sharpe_ratio_return = all_test_roi - risk_free;//夏普值報酬
	all_test_sharpe_ratio = all_test_sharpe_ratio_return / all_test_sharpe_ratio_risk;
}


void sp_test_cal()//測試期夏普值計算
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
		test_sharpe_ratio_risk = test_funds_std_standard_deviation / test_average_funds_std;//夏普值風險
		test_sharpe_ratio_return = test_roi - risk_free;//夏普值報酬
		test_sharpe_ratio = test_sharpe_ratio_return / test_sharpe_ratio_risk;
	}
}

void sharpe_ratio_cal()//訓練期夏普值計算
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
		//cout << "平均資金水位" << fixed << setprecision(20) << average_funds_std[i] << endl;
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
		sharpe_ratio_risk[i] = funds_std_standard_deviation[i] / average_funds_std[i];//夏普值風險
		sharpe_ratio_return[i] = roi[i] - risk_free;//夏普值報酬
		sharpe_ratio[i] = sharpe_ratio_return[i] / sharpe_ratio_risk[i];
		//cout << "夏普值:" << fixed << setprecision(20) << sharpe_ratio[i] << endl;
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
/*單檔趨勢值由大到小排序*/

void sharpe_ratio_compare(int j)//夏普值導引比較
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
	}//找Best&Worst

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
	max_fitness = all_trend_ratio[0];//如果這邊設成0,找到的不一定是當代粒子的最大值。(如果當代粒子都是負的)
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
	}//找Best&Worst

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

void experiment_sp_compare()/*50次實驗Sharpe ratio比較,並找出最好的Sharpe ratio的實驗數*/
{
	Gbest_max_sp = all_sharpe_ratio_max_tmp[0];
	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max_sp <= all_sharpe_ratio_max_tmp[j])
		{
			Gbest_max_sp = all_sharpe_ratio_max_tmp[j];
		}//找50次實驗的Gbest,如果只有一次實驗可註解
	}

	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max_sp == all_sharpe_ratio_max_tmp[j])
		{
			best_experimrentime = j + 1;//找最佳解實驗次數
			break;
		}
	}
	//cout << fixed << setprecision(20) << Gbest_max_sp << endl;
}


void experiment_compre() /*50次實驗Gbest比較,並找出Gbest的實驗數*/
{
	Gbest_max = all_max_tmp[0];
	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max <= all_max_tmp[j])
		{
			Gbest_max = all_max_tmp[j];
		}//找50次實驗的Gbest,如果只有一次實驗可註解
	}

	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max == all_max_tmp[j])
		{
			best_experimrentime = j + 1;//找最佳解實驗次數
			break;
		}
	}
}

void Gbest_sp_num_find()//找最好SP在實驗中出現的次數
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

void Gbest_num_find()//找Gbest於實驗次數中出現的次數
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

void sp_generation_compare()//夏普值世代間比較
{
	for (int j = 0; j < experiment_time; j++)
	{
		for (int t = 0; t < generation; t++)
		{
			for (int i = 0; i < partical_num; i++)
			{
				if (Gbest_max_sp == real_all_sharpe_ratio[j][t][i])
				{
					best_generation = t + 1;//最佳解世代數
					Gbest_daily_risk = all_sp_risk[j][t][i];//最佳解風險
					Gbest_expect_retutn = all_sp_return[j][t][i];//最佳解預期報酬
					Gbest_n = final_n[j][t][i];
					Gbest_share_money = compare_share_money[j][t][i];
					Gbest_i = i;
					for (int k = 0; k < Gbest_n; k++)
					{
						Gbest_all_remain_fund[k] = 0;
						Gbest_buy_lots[k] = compare_buy_lots[j][i][k];//可買張數
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
					best_generation = t + 1;//最佳解世代數
					Gbest_daily_risk = daily_risk[j][t][i];//最佳解風險
					Gbest_expect_retutn = expect_m[j][t][i];//最佳解預期報酬
					Gbest_n = final_n[j][t][i];
					Gbest_share_money = compare_share_money[j][t][i];
					Gbest_i = i;
					for (int k = 0; k < Gbest_n; k++)
					{
						Gbest_all_remain_fund[k] = 0;
						Gbest_buy_lots[k] = compare_buy_lots[j][i][k];//可買張數
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

void Gbest_sp_stock_selection()//記夏普值訓練出的最好投資組合
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
					final_portfolio[s] = stock_no[s];//Gbest投資組合中
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
		string ouput_file = "Larry_result_" + HH_train50[a].substr(0, HH_train50[a].length());//輸出檔案名稱
		output_file.open(ouput_file, ios::app);//檔案輸出
		output_file << "代數" << "," << generation << endl;
		output_file << "粒子數" << "," << partical_num << endl;
		output_file << "旋轉角度上界" << "," << theta << endl;
		output_file << "旋轉角度下界" << "," << theta << endl;
		output_file << "旋轉角度" << "," << theta << endl;
		output_file << "實驗次數" << "," << experiment_time << endl << endl;
		output_file << "初始資金" << "," << initial_fund << endl;
		output_file << "最後資金" << "," << fixed << setprecision(15) << Gbest_yi << endl;
		output_file << "真實報酬" << "," << fixed << setprecision(15) << Gbest_yi - initial_fund << endl << endl;
		output_file << "夏普值報酬" << "," << fixed << setprecision(15) << Gbest_expect_retutn << endl;
		output_file << "夏普值風險" << "," << fixed << setprecision(15) << Gbest_daily_risk << endl;
		output_file << "夏普值" << "," << fixed << setprecision(10) << Gbest_max_sp << endl;
		output_file << "找到最佳解世代" << "," << best_generation << endl;
		output_file << "找到最佳解實驗#" << "," << best_experimrentime << endl;
		output_file << "找到最佳解次數" << "," << Gbest_num << endl << endl;
		output_file << "投資組合檔數" << "," << Gbest_n << endl;
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
		output_file << "股數" << ",";
		for (int k = 0; k < Gbest_n; k++)
		{
			output_file << Gbest_buy_lots[k] << ",";
		}
		output_file << endl;
		output_file << "分配資金" << ",";
		for (int k = 0; k < Gbest_n; k++)
		{
			output_file << Gbest_share_money << ",";
		}
		output_file << endl;
		output_file << "剩餘資金" << ",";
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
		string ouput_file = "Larry_result_" + HH_test50[a].substr(0, HH_test50[a].length());//輸出檔案名稱
		output_file.open(ouput_file, ios::app);//檔案輸出
		output_file << "代數" << "," << generation << endl;//v
		output_file << "粒子數" << "," << partical_num << endl;//v
		output_file << "旋轉角度" << "," << theta << endl;//v
		output_file << "實驗次數" << "," << experiment_time << endl << endl;//v
		output_file << "初始資金" << "," << test_initial_fund << endl;//v
		output_file << "最後資金" << "," << fixed << setprecision(15) << test_all_final_fund << endl;
		output_file << "真實報酬" << "," << fixed << setprecision(15) << test_all_final_fund - test_initial_fund << endl << endl;
		output_file << "預期報酬" << "," << fixed << setprecision(15) << test_sharpe_ratio_return << endl;//v
		output_file << "風險" << "," << fixed << setprecision(15) << test_sharpe_ratio_risk << endl;//v
		output_file << "夏普值" << "," << fixed << setprecision(11) << test_sharpe_ratio << endl;//v
		output_file << endl;
		output_file << "投資組合檔數" << "," << Gbest_n << endl;
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
		output_file << "股數" << ",";

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
		output_file << "分配資金" << ",";
		for (int k = 0; k < Gbest_n; k++)
		{
			output_file << test_share_money << ",";
		}
		output_file << endl;
		output_file << "剩餘資金" << ",";
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
	string ouput_file = "Larry_50_SP_H#_total_test_result.csv";//輸出檔案名稱
	output_file.open(ouput_file, ios::app);//檔案輸出
	output_file << "測試期區間" << "," << "test_2016_Q1-Q2(2015 Q1).csv - test_2019_Q3-Q4(2018 Q1).csv" << endl;
	output_file << "世代數" << "," << generation << endl;
	output_file << "旋轉角度" << "," << theta << endl;
	output_file << "粒子數" << "," << partical_num << endl;
	output_file << "實驗次數" << "," << experiment_time << endl;
	output_file << "初始資金" << "," << initial_fund << endl;
	output_file << "真實報酬" << "," << fixed << setprecision(15) << test_all_final_fund - initial_fund << endl << endl;
	output_file << "預期報酬" << "," << fixed << setprecision(15) << all_test_sharpe_ratio_return << endl;
	output_file << "風險" << "," << fixed << setprecision(15) << all_test_sharpe_ratio_risk << endl;
	output_file << "夏普值" << "," << fixed << setprecision(10) << all_test_sharpe_ratio << endl;
	output_file << "總天數" << "," << total_test_day << endl;
	output_file << "天數" << "," << "總資金水位" << endl;
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

void all_sp_train_prtiod_result(int a)//夏普值所有訓練期結果輸出
{
	string ouput_file = "Larry_50_H#_train_Gbest_10000_10_50_0.0004.csv";//輸出檔案名稱
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
		output_file << "夏普值" << "," << fixed << setprecision(20) << all_file_best_sp[a] << ",";
		output_file << "預期報酬" << "," << fixed << setprecision(20) << all_file_gbest_return[a] << ",";
		output_file << "風險" << "," << fixed << setprecision(20) << all_file_gbest_risk[a] << ",";
		output_file << "最佳解實驗#" << "," << all_file_gbest_experiment[a] << ",";
		output_file << "最佳解世代#" << "," << all_file_gbest_generation[a] << ",";
		output_file << "最佳解出現次數" << "," << all_file_gbest_appear[a];
		output_file << endl;
	}
	output_file.close();
}

void sp_testing_period(int a)
{

	string ouput_file = "Larry_50_H#_SP_test_Gbest_10000_10_50_0.0004.csv";//輸出檔案名稱
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
	output_file << "夏普值" << "," << fixed << setprecision(20) << final_test_period_sharpe_ratio[a] << ",";
	output_file << "預期報酬" << "," << fixed << setprecision(20) << final_test_period_sharpe_return[a] << ",";
	output_file << "風險" << "," << fixed << setprecision(20) << final_test_period_sharpe_ratio_risk[a] << ",";
	output_file << endl;
	output_file.close();
}


void single_output(int a)
{
	string ouput_file = "Larry_US50_Q2Q_train_single_result.csv";//輸出檔案名稱
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
					output_file << all_stock_no[a][u] << "," << "趨勢值" << "," << fixed << setprecision(15) << all_single_trend_ratio[a][i];
					output_file << "," << "預期報酬" << "," << fixed << setprecision(15) << all_single_m[a][u] << "," << "風險" << "," << fixed << setprecision(15) << all_single_risk[a][u];
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
				//single_compare();//單檔趨勢值排序
				sharpe_ratio_cal();//夏普值導引
				sharpe_ratio_compare(j);//夏普值導引比較
										//compare();//趨勢值導引比較
				for (int i = 0; i < partical_num; i++)
				{
					all_stock_no[a][i] = '/0';
					//real_all_trend_ratio[j][t][i] = all_trend_ratio[i];//趨勢值
					daily_risk[j][t][i] = risk[i];
					expect_m[j][t][i] = m[i];
					final_n[j][t][i] = n[i];
					compare_share_money[j][t][i] = all_share_money[i];

					all_all_trend_ratio[a][i] = all_trend_ratio[i];
					all_single_trend_ratio[a][i] = single_trend_ratio[i];
					all_stock_no[a][i] = stock_no[i];
					all_single_m[a][i] = m[i];
					all_single_risk[a][i] = risk[i];
					/*趨勢值*/

					real_all_sharpe_ratio[j][t][i] = sharpe_ratio[i];//夏普值
					all_sp_risk[j][t][i] = sharpe_ratio_risk[i];
					all_sp_return[j][t][i] = sharpe_ratio_return[i];
					/*夏普值*/
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
			all_max_tmp[j] = all_max;//將每次實驗找到的Gbest放入陣列中	
			all_sharpe_ratio_max_tmp[j] = all_max_sharpe_ratio;
			//cout << all_sharpe_ratio_max_tmp[j] << endl;
			//cout << fixed << setprecision(20) << all_sharpe_ratio_max_tmp[j] << endl;
		}
		//experiment_compre();
		experiment_sp_compare();//找實驗最好的夏普值
								//Gbest_num_find();
		Gbest_sp_num_find();//找實驗中最好夏普值出現的次數
							//generation_compare();
		sp_generation_compare();//夏普值世代數比較
		Gbest_sp_stock_selection();//記夏普值訓練出的最好投資組合
								   //out_file(a);
		sp_out_file(a);//夏普值輸出
		test_index = 0;
		test_read_file(a);//測試期讀檔
		if (a == 0)
		{
			test_initial_fund = initial_fund;//如果是第一個測試期檔案,則初始資金為10000000
		}
		if (test_all_final_fund <= 0)
		{
			test_initial_fund = test_initial_fund;
		}
		else if (a != 0)
		{
			test_initial_fund = test_all_final_fund;//第二個測試期檔案開始,初始資金為上一區間最後資金

		}
		test_standardization(a);
		//single_output(a);//單檔投資組合輸出
		//test_fitness(a);//趨勢值測試期
		sp_test_cal();
		//all_test_return();//總體測試期預期報酬計算
		if (Gbest_max_sp > 0)
		{
			final_test_period_sharpe_ratio[a] = test_sharpe_ratio;
			final_test_period_sharpe_ratio_risk[a] = test_sharpe_ratio_risk;
			final_test_period_sharpe_return[a] = test_sharpe_ratio_return;
		}

		sp_test_out_file(a);//趨勢值測試期檔案輸出

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
		all_sp_train_prtiod_result(a);//夏普值各訓練期結果輸出
									  //all_train_prtiod_result(a);
		if (Gbest_max_sp > 0)
		{
			sp_testing_period(a);//測試期各區間輸出
		}
	}
	all_test_sp_cal();
	//all_test_risk();//總體測試期風險計算
	all_testperiod_final_result();//總體測試期結果輸出
	cout << endl << (double)clock() / CLOCKS_PER_SEC << "S" << endl;
	system("pause");
	return 0;
}