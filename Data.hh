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
  double binCenter(int i) const { return m_bins.size()/2; }
  double binLow(int i) const { return *min_element(m_bins.begin(), m_bins.end()); }
  double binHigh(int i) const { return *max_element(m_bins.begin(), m_bins.end()); }
  double error(int i) const { return m_error[i]; }
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

  

 private:
  Data() {}  // disallow empty data set
  void assertSizes();
  std::vector<double> m_data;
  std::vector<double> m_bins;
  std::vector<double> m_error;
  
};



#endif
