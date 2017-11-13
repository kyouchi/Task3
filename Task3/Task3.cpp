// Task3.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <vector>
#include <memory>
#include "../GPlotTools/plot.h"
#include <iostream>
#include "../FFT/fft.h"

int main()
{
   const auto A = 1.0;
   const auto tau = 1.0;
   const auto fs = 8192;//サンプリング周波数(2のべき乗)
   const auto pi = 3.141592653589793;//円周率
   std::vector<double> Fc = { 10,50,100 };
   /*
   std::unique_ptr<double[]> t(new double [2*fs]);
   std::unique_ptr<double[]> v(new double [2*fs]);
   */
   std::vector<double> t;
   std::vector<std::complex<double>> v;
   t.resize(2 * fs);
   v.resize(2 * fs);
   for(auto i = 0; i < 2 * fs; ++i)
   {
      t[i] = (i / static_cast<double>(fs)) - 1.0;
      if(fs*(1-tau/2.0) < i && fs*(1+tau/2.0) > i)
      {
         if (fs > i) {
            v[i] = (A / (fs*(1-tau/2.0))) * i - A;
         }
         else
         {
            v[i] = ((1/(tau/2.0))+1) * A - (A / (fs*(1-tau/2.0))) * i;
         }
      }
      else
      {
         v[i] = (0.0,0.0);
      }
   }

   plot(t, v, "t[sec]", "Amplitude", "Waveform", "waveform.plt", "command.bat").executionPlot();

   //Apply FFT
   std::vector<int> ids;
   auto n_level = lc_fft_calc_ids(2 * fs, &ids);// FFT事前計算
   std::vector<std::complex<double>> output;
   lc_fft(v, ids, n_level, &output);// FFT変換

   std::vector<double> f;
   f.resize(output.size());
   for (unsigned int i = 0; i < output.size(); ++i)f[i] = static_cast<double>(i)/2.0;
   plot(f, output, "f[Hz]", "Amplitude", "Apply FFT", "FFT.plt", "commandFFT.bat").executionPlot_abs();

   for(auto fc : Fc)
   {
      std::vector<double> t2;
      std::vector<std::complex<double>> v2;
      t2.resize(2 * fs);
      v2.resize(2 * fs);

      for(auto i = 0; i < 2 * fs; ++i)
      {
         t2[i] = (i / static_cast<double>(fs)) - 1.0;
         if(fs*(1-tau/2.0) < i && fs*(1+tau/2.0) > i)
         {
            if (fs > i) {
               v2[i] = (A / (fs*(1-tau/2.0))) * i - A;
            }
            else
            {
               v2[i] = ((1/(tau/2.0))+1) * A - (A / (fs*(1-tau/2.0))) * i;
            }
         }
         else
         {
            v2[i] = (0.0,0.0);
         }
         v2[i] *= std::cos(2.0 * pi * static_cast<double>(fc) * ((static_cast<double>(i)/static_cast<double>(fs))-1.0));//Cosineを乗算
      }
      plot(t2, v2, "t[sec]", "Amplitude", "Waveform", "waveform"+std::to_string(fc)+".plt", "command"+std::to_string(fc)+".bat").executionPlot();

      //Apply FFT
      std::vector<int> ids2;
      auto n_level2 = lc_fft_calc_ids(2 * fs, &ids2);// FFT事前計算
      std::vector<std::complex<double>> output2;
      lc_fft(v2, ids2, n_level2, &output2);// FFT変換

      std::vector<double> f2;
      f2.resize(output2.size());
      for (unsigned int i = 0; i < output2.size(); ++i)f2[i] = static_cast<double>(i)/2.0;
      plot(f2, output2, "f[Hz]", "Amplitude", "Apply FFT", "FFT"+std::to_string(fc)+".plt", "commandFFT"+std::to_string(fc)+".bat").executionPlot_abs();

   }
   return 0;
}
