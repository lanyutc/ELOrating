

#ifndef _ELORATING_H_
#define _ELORATING_H_

#include <math.h>

static const unsigned int deno = 400;



static const double novice  = 1000.0;  //0-999 初学者
static const double someExp = 1500.0;  //1000-1499 有经验者
static const double skill   = 2000.0;  //1500-1999 熟练者
static const double expert  = 2200.0;  //2000-2199 专家
static const double master  = 2400.0;  //2200-2399 大师 >2400 宗师




/**
* @brief         自适应k值
*
* @param score   积分
* @param isWin   胜负因子
*
* @returns       k值结果
*/
static inline unsigned int adaptationK(double score, bool isWin)
{
	return score < novice ? (32.0 + (isWin ? 32.0:0.0)): 
		   score < someExp ? (32.0 + (isWin ? 16.0:0.0)):
		   score < skill ? 32.0 :
		   score < expert ? 20.0 :
		   score < master ? 15.0 : 10.0;
}


/**
* @brief    计算a相对b的胜率
*
* @param a  a的积分
* @param b  b的积分
*
* @returns  胜率
*/
static inline double getWinRate(double a, double b)
{
	return 1 / (1 + pow(10, (b-a)/deno));
}


/**
* @brief        计算积分变化
*
* @param a      a的积分
* @param b      b的积分
* @param isWin  a对b的胜负关系 true-a胜 false-a败
* @param isDraw a对b是否平局   true-平（不查看isWin字段） false-有胜负（查看isWin字段）
*
* @returns      a的积分变化 
*/
static inline double getScoreChg(double a, double b, bool isWin, bool isDraw)
{
	double w       = isDraw ? 0.5 : (isWin ? 1.0 : 0.0);
	double winRate = getWinRate(a, b);
	return (w - winRate) * adaptationK(a, isWin);
}



/**
* @brief         计算积分结果
*
* @param a       a的积分
* @param b       b的积分
* @param isWin   a对b的胜负关系 true-a胜 false-a败
* @param isDraw  a对b是否平局   true-平（不查看isWin字段） false-有胜负（查看isWin字段）
*
* @returns       a的积分终值
*/
static inline double calcResult(double a, double b, bool isWin, bool isDraw)
{
	return (a + getScoreChg(a, b, isWin, isDraw));
}

#endif
