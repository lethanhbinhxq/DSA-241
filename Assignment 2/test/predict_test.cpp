  // test funtion predict DataLoader
  double_tensor predict_DataLoader = pretrained1.predict(&test_loader, false);
  double_tensor expect_3 = {
      0., 0., 0., 1., 1., 1., 0., 1., 1., 0., 0., 1., 1., 0., 1., 1., 0.,
      1., 0., 0., 1., 0., 1., 0., 0., 0., 0., 0., 1., 1., 0., 0., 0., 0.,
      1., 1., 1., 1., 1., 0., 0., 1., 0., 0., 1., 1., 0., 0., 1., 0., 1.,
      1., 0., 1., 1., 0., 1., 0., 1., 0., 1., 0., 0., 0., 0., 1., 0., 1.,
      0., 1., 0., 1., 1., 0., 1., 1., 0., 1., 1., 1., 0., 0., 0., 1., 1.,
      0., 1., 0., 1., 0., 0., 1., 1., 0., 0., 1., 1., 0., 0., 1., 0., 0.,
      1., 1., 1., 1., 0., 0., 1., 1., 1., 0., 1., 1., 0., 1., 0., 0., 1.,
      0., 0., 1., 1., 1., 0., 0., 1., 1., 0., 0., 1., 0., 0., 1., 0., 1.,
      0., 1., 0., 1., 1., 1., 1., 0., 0., 0., 0., 1., 0., 0., 1., 1., 0.,
      0., 0., 0., 1., 1., 0., 0., 1., 1., 1., 1., 0., 0., 1., 0., 1., 0.,
      0., 0., 0., 0., 1., 1., 1., 0., 1., 1., 0., 0., 1., 1., 1., 1., 0.,
      1., 0., 0., 1., 1., 0., 1., 0., 1., 0., 0., 1., 1.};
  cout << "predict : ";
  for (const auto& val : predict_DataLoader) {
    std::cout << val << " ";
  }
  cout << endl;

  cout << "expect  : ";
  for (const auto& val : expect_3) {
    std::cout << val << " ";
  }
  cout << endl;

  int correct = 0;
  for (size_t i = 0; i < predict_DataLoader.size(); ++i) {
    if (predict_DataLoader(i) == expect_3(i)) {
      ++correct;
    }
  }

  // 0.995
  std::cout << "Accuracy: "
            << static_cast<double>(correct) / predict_DataLoader.size()
            << std::endl;
  std::cout << "expect Accuracy: " << 0.995 << std::endl;
}