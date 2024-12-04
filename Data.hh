#ifndef DATA_HH
#define DATA_HH

#include <vector>
#include <string>
//#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <cmath>

class Data {
 public:
  Data(const std::string& filename);

  unsigned int size() const { return m_data.size(); }
  double measurement(int i) const { return m_data[i]; }
  double binCenter(int i) const { return m_bins[i] + (m_bins[i+1]-m_bins[i])/2; }
  double binLow(int i) const { return *min_element(m_bins.begin(), m_bins.end()); }
  double binHigh(int i) const { return *max_element(m_bins.begin(), m_bins.end()); }
  double error(int i) const { return m_error[i]; }
  double bin(int i) const { return m_bins[i]; }
  int checkCompatibility( const Data& in , int n ) const {    
      int zaehler = 0;
      for(int i = 0; i < 56; i++){
        if(in.measurement(i) - measurement(i) > n * sqrt(pow(error(27), 2) +  pow(in.error(27), 2))){
          zaehler++;
        }
        if (in.measurement(i) - measurement(i) < -n * sqrt(pow(error(27), 2) +  pow(in.error(27), 2))){
          zaehler++;
        }
      }
      return zaehler;
  }
  double prediction(int i) const {return 0.005 - 0.00001 * binCenter(i) + 0.08*exp(-0.015 * binCenter(i)); }
  double rechi2() const { 
    double chi2 = 0.0;
    for (int i = 0; i < 56; ++i) {
    chi2 +=  pow(measurement(i) - prediction(i),2)/pow(error(i),2);
    }
    return chi2/56;
  }



  Data plus(const Data& A) {
  // Kompatibilität checken:
  if (checkCompatibility(A, 1) == 0){
    return A;
  }
  double new_error;
  double y;
  for(int i = 0; i < 56; i++){
    y = (1/pow(A.error(i), 2)*A.measurement(i) + 1/pow(error(i), 2)*measurement(i))/(1/pow(A.error(i), 2) + 1/pow( error(i), 2));
    new_error = sqrt(1/(1/pow(A.error(i), 2) + 1/pow( error(i), 2)));
    m_data.push_back(y);
    m_error.push_back(new_error);
  }
  }

 private:
  Data() {}  // disallow empty data set
  void assertSizes();
  std::vector<double> m_data;
  std::vector<double> m_bins;
  std::vector<double> m_error;
};



#endif
