#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  VectorXd rmse = VectorXd(4);
  rmse << 0, 0, 0, 0;

  cout << "CalculateRMSE: " << endl;
  //cout << ground_truth.size() << endl;

  // check the validity of the following inputs:
  //  * the estimation vector size should not be zero
  //  * the estimation vector size should equal ground truth vector size
  if (estimations.size() != ground_truth.size() || 
      estimations.size() == 0) {
    std::cout << "Invalid estimation or ground_truth data!!!" << std::endl;
    return rmse;
  }

  //accumulate squared residuals
  for (unsigned int i = 0; i < estimations.size(); ++i){

    VectorXd residual = estimations[i] - ground_truth[i];

    //coefficient-wise multiplication
    residual = residual.array()*residual.array();
    rmse += residual;
  }

  //calculate the mean
  rmse = rmse / estimations.size();

  //calculate the squared root
  rmse = rmse.array().sqrt();

  std::cout << "ground_truth: "; 
  std::cout << ground_truth[0] << endl;

  // std::cout << "estimations: "; 
  // std::cout << estimations[0] << estimations[1] << estimations[2] << estimations[3] << endl;
  // std::cout << "rmse: "; std::cout << rmse[0] << rmse[1] << rmse[2] << rmse[3] << endl;

  //return the result
  return rmse;
}