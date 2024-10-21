/*
 * Assignment 1 - Developing List Data Structures and Artificial Neural Networks
 * file : unit_test.cpp
 * Data Structures and Algorithms
 * Author: Võ Tiến
 * Link FB : https://www.facebook.com/Shiba.Vo.Tien
 * Link Group : https://www.facebook.com/groups/khmt.ktmt.cse.bku
 * Date: 10.9.2024
 */
#include "unit_test.hpp"
#include "../[DataLoader] C++ samples and outputs-20241008/DataLoaderDemo.h"
map<string, bool (T_Data::*)()> T_Data::TESTS;

bool T_Data::data1() {
  string name = "data1";
  //! data
  xt::xarray<float> data = {1., 2., 3.};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset tensor(data, label);

  //! expect
  string expect = "len=3";

  //! output
  string output = "len=" + to_string(tensor.len());

  //! remove data

  //! print result
  return printResult(output, expect, name);
}

bool T_Data::data2() {
  string name = "data2";
  //! data
  xt::xarray<float> data = {{1., 2., 3.}, {1., 2., 3.}};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset tensor(data, label);

  //! expect
  string expect = "len=2";

  //! output
  string output = "len=" + to_string(tensor.len());

  //! remove data

  //! print result
  return printResult(output, expect, name);
}

bool T_Data::data3() {
  string name = "data3";
  //! data
  xt::xarray<float> data = {{{1., 2., 3.}, {1., 2., 3.}}};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset tensor(data, label);

  //! expect
  string expect = "len=1";

  //! output
  string output = "len=" + to_string(tensor.len());

  //! remove data

  //! print result
  return printResult(output, expect, name);
}

bool T_Data::data4() {
  string name = "data4";

  //! data
  xt::xarray<float> data = {1., 2., 3.};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset tensor(data, label);

  xt::svector<unsigned long> get_data_shape = tensor.get_data_shape();
  xt::svector<unsigned long> get_label_shape = tensor.get_label_shape();

  //! expect
  string expect = "data_shape=[3] label_shape=[3]";

  //! output
  stringstream ss;
  ss << "data_shape=[";
  for (size_t i = 0; i < get_data_shape.size(); ++i) {
    ss << get_data_shape[i];
    if (i != get_data_shape.size() - 1) {
      ss << ", ";
    }
  }
  ss << "] label_shape=[";
  for (size_t i = 0; i < get_label_shape.size(); ++i) {
    ss << get_label_shape[i];
    if (i != get_label_shape.size() - 1) {
      ss << ", ";
    }
  }
  ss << "]";

  string output = ss.str();

  //! print result
  return printResult(output, expect, name);
}

bool T_Data::data5() {
  string name = "data5";
  //! data
  xt::xarray<float> data = {{1., 2., 3.}, {1., 2., 3.}};
  xt::xarray<float> label = {{1., 2., 3.}, {1., 2., 3.}, {1., 2., 3.}};
  TensorDataset tensor(data, label);
  xt::svector<unsigned long> get_data_shape = tensor.get_data_shape();
  xt::svector<unsigned long> get_label_shape = tensor.get_label_shape();

  //! expect
  string expect = "data_shape=[2, 3] label_shape=[3, 3]";

  //! output
  stringstream ss;
  ss << "data_shape=[";
  for (size_t i = 0; i < get_data_shape.size(); ++i) {
    ss << get_data_shape[i];
    if (i != get_data_shape.size() - 1) {
      ss << ", ";
    }
  }
  ss << "] label_shape=[";
  for (size_t i = 0; i < get_label_shape.size(); ++i) {
    ss << get_label_shape[i];
    if (i != get_label_shape.size() - 1) {
      ss << ", ";
    }
  }
  ss << "]";

  string output = ss.str();

  //! print result
  return printResult(output, expect, name);
}

bool T_Data::data6() {
  string name = "data6";
  //! data
  xt::xarray<float> data = {{{1., 2., 3.}, {1., 2., 3.}}};
  xt::xarray<double>::shape_type shape = {2, 3, 1};
  xt::xarray<string> label(shape);

  TensorDataset tensor(data, label);
  xt::svector<unsigned long> get_data_shape = tensor.get_data_shape();
  xt::svector<unsigned long> get_label_shape = tensor.get_label_shape();

  //! expect
  string expect = "data_shape=[1, 2, 3] label_shape=[2, 3, 1]";

  //! output
  stringstream ss;
  ss << "data_shape=[";
  for (size_t i = 0; i < get_data_shape.size(); ++i) {
    ss << get_data_shape[i];
    if (i != get_data_shape.size() - 1) {
      ss << ", ";
    }
  }
  ss << "] label_shape=[";
  for (size_t i = 0; i < get_label_shape.size(); ++i) {
    ss << get_label_shape[i];
    if (i != get_label_shape.size() - 1) {
      ss << ", ";
    }
  }
  ss << "]";

  string output = ss.str();

  //! print result
  return printResult(output, expect, name);
}

bool T_Data::data7() {
  string name = "data7";
  //! data
  xt::xarray<float> data = {{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset tensor(data, label);
  DataLabel<float, string> getitem = tensor.getitem(0);
  xt::xarray<float> getData = getitem.getData();
  xt::xarray<string> getLabel = getitem.getLabel();
  //! expect
  string expect = "data= { 1.,  2.,  3.} label=one";

  //! output
  stringstream ss;
  ss << "data= " << getData << " " << "label=" << getLabel;
  string output = ss.str();

  //! remove data

  //! print result
  return printResult(output, expect, name);
}

bool T_Data::data8() {
  string name = "data8";
  //! data
  xt::xarray<float> data = {{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset tensor(data, label);
  DataLabel<float, string> getitem = tensor.getitem(2);
  xt::xarray<float> getData = getitem.getData();
  xt::xarray<string> getLabel = getitem.getLabel();
  //! expect
  string expect = "data= { 7.,  8.,  9.} label=three";

  //! output
  stringstream ss;
  ss << "data= " << getData << " " << "label=" << getLabel;
  string output = ss.str();

  //! remove data

  //! print result
  return printResult(output, expect, name);
}

bool T_Data::data9() {
  string name = "data9";
  //! data
  xt::xarray<float> data = {{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset tensor(data, label);
  //! expect
  string expect = "Error: Out of range exception: Index is out of range!";

  //! output
  string output = "";
  try {
    DataLabel<float, string> getitem = tensor.getitem(3);
  } catch (const std::out_of_range &e) {
    output = "Error: Out of range exception: " + string(e.what());
  }

  //! remove data

  //! print result
  return printResult(output, expect, name);
}
bool T_Data::data10() {
  string name = "data10";
  //! data
  xt::xarray<float> data = {{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset tensor(data, label);
  //! expect
  string expect = "Error: Out of range exception: Index is out of range!";

  //! output
  string output = "";
  try {
    DataLabel<float, string> getitem = tensor.getitem(-1);
  } catch (const std::out_of_range &e) {
    output = "Error: Out of range exception: " + string(e.what());
  }

  //! remove data

  //! print result
  return printResult(output, expect, name);
}

bool T_Data::data11() {
  string name = "data11";
  //! data
  int nsamples = 100;
  xt::xarray<float> data = {1, 2, 3};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset<double, string> ds(data, label);
  DataLoader<double, string> loader(&ds, 3, false, false);
  //! expect
  string expect = "getData={ 1.,  2.,  3.} ; getLabel={  one,   two, three} ";

  //! output

  stringstream output;
  output << "getData=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getData() << " ";
  }
  output << "; getLabel=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getLabel() << " ";
  }
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data12() {
  string name = "data12";
  //! data
  int nsamples = 100;
  xt::xarray<float> data = {1, 2, 3, 4};
  xt::xarray<string> label = {"one", "two", "three", "four"};
  TensorDataset<double, string> ds(data, label);
  DataLoader<double, string> loader(&ds, 3, false, false);
  //! expect
  string expect =
      "getData={ 1.,  2.,  3.} { 4.} ; getLabel={  one,   two, three} {four} ";

  // string expect =
  //     "getData={ 1.,  2.,  3.,  4.} ; getLabel={  one,   two, three,  four} ";

  //! output

  stringstream output;
  output << "getData=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getData() << " ";
  }
  output << "; getLabel=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getLabel() << " ";
  }
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data13() {
  string name = "data13";
  //! data
  int nsamples = 100;
  xt::xarray<float> data = {1, 2, 3, 4};
  xt::xarray<string> label = {"one", "two", "three", "four"};
  TensorDataset<double, string> ds(data, label);
  DataLoader<double, string> loader(&ds, 3, false, true);
  //! expect
  string expect =
      "getData={ 1.,  2.,  3.,  4.} ; getLabel={  one,   two, three,  four} ";

  // string expect =
  //     "getData={ 1.,  2.,  3.} ; getLabel={  one,   two, three} ";

  //! output

  stringstream output;
  output << "getData=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getData() << " ";
  }
  output << "; getLabel=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getLabel() << " ";
  }
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data14() {
  string name = "data14";
  //! data
  int nsamples = 100;
  xt::xarray<float> data = {1, 2};
  xt::xarray<string> label = {"one", "two"};
  TensorDataset<double, string> ds(data, label);
  DataLoader<double, string> loader(&ds, 3, false, true);
  //! expect
  string expect = "getData={ 1.,  2.} ; getLabel={one, two} ";

  //! output

  stringstream output;
  output << "getData=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getData() << " ";
  }
  output << "; getLabel=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getLabel() << " ";
  }
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data15() {
  string name = "data15";
  //! data
  int nsamples = 100;
  xt::xarray<float> data = {1};
  xt::xarray<string> label = {"one"};
  TensorDataset<double, string> ds(data, label);
  DataLoader<double, string> loader(&ds, 3, false, false);
  //! expect
  string expect = "getData={ 1.} ; getLabel={one} ";

  //! output

  stringstream output;
  output << "getData=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getData() << " ";
  }
  output << "; getLabel=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getLabel() << " ";
  }
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data16() {
  string name = "data16";
  //! data
  xt::xarray<float> data = {{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset<double, string> ds(data, label);
  DataLoader<double, string> loader(&ds, 4, false, false);
  //! expect
  string expect =
      "getData={{ 1.,  2.,  3.},\n { 4.,  5.,  6.},\n { 7.,  8.,  9.}} ; "
      "getLabel={  one,   two, three} ";

  //! output

  stringstream output;
  output << "getData=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getData() << " ";
  }
  output << "; getLabel=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getLabel() << " ";
  }
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data17() {
  string name = "data17";
  //! data
  xt::xarray<float> data = {{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset<double, string> ds(data, label);
  DataLoader<double, string> loader(&ds, 3, false, false);
  //! expect
  string expect =
      "getData={{ 1.,  2.,  3.},\n { 4.,  5.,  6.},\n { 7.,  8.,  9.}} ; "
      "getLabel={  one,   two, three} ";

  //! output

  stringstream output;
  output << "getData=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getData() << " ";
  }
  output << "; getLabel=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getLabel() << " ";
  }
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data18() {
  string name = "data18";
  //! data
  xt::xarray<float> data = {{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset<double, string> ds(data, label);
  DataLoader<double, string> loader(&ds, 2, false, false);
  //! expect
  string expect =
      "getData={{ 1.,  2.,  3.},\n { 4.,  5.,  6.}} {{ 7.,  8.,  9.}} ; "
      "getLabel={one, "
      "two} {three} ";

  //! output

  stringstream output;
  output << "getData=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getData() << " ";
  }
  output << "; getLabel=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getLabel() << " ";
  }
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data19() {
  string name = "data19";
  //! data
  int nsamples = 100;
  xt::xarray<double> X = xt::random::randn<double>({nsamples, 10});
  xt::xarray<double> T = xt::random::randn<double>({nsamples, 5});
  TensorDataset<double, double> ds(X, T);
  DataLoader<double, double> loader(&ds, 30, true, false);
  //! expect
  string expect =
      "(30, 10);(30, 5) (30, 10);(30, 5) (30, 10);(30, 5) (10, 10);(10, 5) ";

  //! output

  stringstream output;
  for (auto batch : loader) {
    output << shape2str(batch.getData().shape()) << ";";
    output << shape2str(batch.getLabel().shape()) << " ";
  }
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data20() {
  string name = "data20";
  //! data
  int nsamples = 120;
  xt::xarray<double> X = xt::random::randn<double>({nsamples, 10, 5});
  xt::xarray<double> T = xt::random::randn<double>({nsamples, 5, 5});
  TensorDataset<double, double> ds(X, T);
  DataLoader<double, double> loader(&ds, 30, true, false);
  //! expect
  string expect =
      "(30, 10, 5);(30, 5, 5) (30, 10, 5);(30, 5, 5) (30, 10, 5);(30, 5, 5) "
      "(30, 10, 5);(30, 5, 5) ";

  //! output

  stringstream output;
  for (auto batch : loader) {
    output << shape2str(batch.getData().shape()) << ";";
    output << shape2str(batch.getLabel().shape()) << " ";
  }
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data21() {
  string name = "data21";
  //! data
  int nsamples = 100;
  xt::xarray<double> X = xt::random::randn<double>({nsamples, 1, 2, 3});
  xt::xarray<double> T = xt::random::randn<double>({nsamples, 1, 2, 3});
  TensorDataset<double, double> ds(X, T);
  DataLoader<double, double> loader(&ds, 30, true, true);
  //! expect
  string expect =
      "(30, 1, 2, 3);(30, 1, 2, 3) (30, 1, 2, 3);(30, 1, 2, 3) (40, 1, 2, "
      "3);(40, 1, 2, 3) ";

  //! output

  stringstream output;
  for (auto batch : loader) {
    output << shape2str(batch.getData().shape()) << ";";
    output << shape2str(batch.getLabel().shape()) << " ";
  }
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data22() {
  string name = "data22";
  //! data
  int nsamples = 70;
  xt::xarray<double> X = xt::random::randn<double>({nsamples, 1});
  xt::xarray<double> T = xt::random::randn<double>({nsamples, 1});
  TensorDataset<double, double> ds(X, T);
  DataLoader<double, double> loader(&ds, 30, true, false);
  //! expect
  string expect = "(10, 1) (10, 1)";

  //! output

  stringstream output;
  auto batch = loader.begin();
  Batch b = *(++batch);
  output << shape2str(b.getData().shape()) << " ";
  output << shape2str(b.getLabel().shape());
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data23() {
  string name = "data23";
  //! data
  int nsamples = 70;
  xt::xarray<double> X = xt::random::randn<double>({nsamples, 1});
  xt::xarray<double> T = xt::random::randn<double>({nsamples, 1});
  TensorDataset<double, double> ds(X, T);
  DataLoader<double, double> loader(&ds, 30, true, false);
  //! expect
  string expect = "(30, 1) (30, 1)";

  //! output

  stringstream output;
  auto batch = loader.begin();
  Batch b = *(batch++);
  output << shape2str(b.getData().shape()) << " ";
  output << shape2str(b.getLabel().shape());
  //! remove data

  //! print result
  return printResult(output.str(), expect, name);
}

bool T_Data::data24() {
  case_data_wo_label_1();
  return false;
}

bool T_Data::data25() {
  case_data_wi_label_1();
  return false;
}

bool T_Data::data26() {
  case_batch_larger_nsamples();
  return false;
}

struct CustomType {
    int id;
    float value;
    
    friend ostream& operator<<(ostream& os, const CustomType& c) {
        os << "{ id: " << c.id << ", value: " << c.value << " }";
        return os;
    }
};


bool T_Data::data27() {
   // Create a dataset using custom struct with xt::xarray
    xt::xarray<int> X_id = {{1, 2}, {3, 4}}; // 2x2 matrix for IDs
    xt::xarray<double> X_value = {{2.5, 3.5}, {4.5, 5.5}}; // 2x2 matrix for values
    xt::xarray<int> t = {1, 0, 1, 0}; // 4 Labels, matching data points

    // Pack custom data into xt::xarray
    xt::xarray<CustomType> X = {
        CustomType{X_id(0, 0), X_value(0, 0)},
        CustomType{X_id(0, 1), X_value(0, 1)},
        CustomType{X_id(1, 0), X_value(1, 0)},
        CustomType{X_id(1, 1), X_value(1, 1)}
    };

    cout << "############################################" << endl;
    cout << "# CASE: CUSTOM DATA TYPE WITH 2D XTENSOR" << endl;
    cout << "############################################" << endl;
    cout << "ORIGINAL data and label:" << endl;
    cout << "X shape: " << shape2str(X.shape()) << endl;
    cout << "X: " << endl;
    for (const auto& x : X) cout << x << endl;
    cout << "t: " << endl << t << endl;
    cout << "=================================" << endl;

    // Create TensorDataset and DataLoader
    TensorDataset<CustomType, int> ds(X, t);
    int batch_size = 2; // Set batch size
    bool shuffle = true, drop_last = false;
    int seed = 100;

    DataLoader<CustomType, int>* pLoader;

    cout << "Loading with shuffle=true + seed=100:" << endl;
    cout << "################################" << endl;
    pLoader = new DataLoader<CustomType, int>(&ds, batch_size, shuffle, drop_last, seed);

    int batch_idx = 1;
    for (auto batch : *pLoader) {
        cout << "batch_idx:" << batch_idx++ << endl;
        cout << "data:" << endl;
        for (const auto& x : batch.getData()) cout << x << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    delete pLoader;
    cout << endl << endl;
  return false;
}