#include <fmt_formatters.h>

#include <catch2/catch_test_macros.hpp>

/**
  fmt version summary:
  Ubuntu 20.04 (Focal)	6.1.2
  Ubuntu 22.04 (Jammy)	8.1.1 -> has std::ostream support
  Ubuntu 24.04 (Noble)	9.1.0 -> automatics std::ostream support was removed
*/

TEST_CASE("Eigen fixed size types can be formatted with fmt", "[fmt][eigen]") {
  Eigen::Vector3d v(1.0, 2.0, 3.0);
  Eigen::Matrix3d m = Eigen::Matrix3d::Identity();

  // Just check that formatting compiles
  REQUIRE_FALSE(fmt::format("Vector: {}", v).empty());
  REQUIRE_FALSE(fmt::format("Matrix:\n{}", m).empty());
  REQUIRE_FALSE(fmt::format("Matrix transpose:\n{}", m.transpose()).empty());

  // Test print
  fmt::print("Vector: {}", v);
  fmt::print("Matrix: {}", m);
}

TEST_CASE("Eigen dynamic size types can be formatted with fmt",
          "[fmt][eigen]") {
  Eigen::VectorXd v(3);
  v << 1.0, 2.0, 3.0;
  Eigen::MatrixXd m(3, 3);
  m = Eigen::Matrix3d::Identity();

  // Just check that formatting compiles
  REQUIRE_FALSE(fmt::format("Vector: {}", v).empty());
  REQUIRE_FALSE(fmt::format("Matrix:\n{}", m).empty());
  REQUIRE_FALSE(fmt::format("Matrix transpose:\n{}", m.transpose()).empty());

  // Test print
  fmt::print("Vector: {}", v);
  fmt::print("Matrix: {}", m);
}

TEST_CASE("sva::PTransformd can be formatted with fmt", "[fmt][ptransform]") {
  Eigen::Vector3d translation(1.0, 2.0, 3.0);
  Eigen::Matrix3d rotation = Eigen::Matrix3d::Identity();
  sva::PTransformd pt(rotation, translation);

  std::string pt_str = fmt::format("PTransform:\n{}", pt);
  fmt::print("PTransform:\n{}", pt);

  REQUIRE_FALSE(pt_str.empty());
}

template <typename T>
void check_fmt_nonempty(const std::string& label, const T& value) {
  REQUIRE_FALSE(fmt::format("{}: {}", label, value).empty());
  fmt::print("{}: {}\n", label, value);
}

#define SVA_FMT_TEST(TYPE, METHOD) check_fmt_nonempty(#TYPE, TYPE::METHOD());

#define SVA_FMT_TEST_CTOR(TYPE) check_fmt_nonempty(#TYPE, TYPE{});

TEST_CASE("All sva types can be formatted with fmt", "[fmt][sva]") {
  SVA_FMT_TEST_CTOR(sva::ABInertiad) SVA_FMT_TEST(sva::AdmittanceVecd, Zero);
  SVA_FMT_TEST(sva::ForceVecd, Zero) SVA_FMT_TEST(sva::MotionVecd, Zero);
  SVA_FMT_TEST_CTOR(sva::RBInertiad);
  SVA_FMT_TEST(sva::PTransformd, Identity);
  SVA_FMT_TEST(sva::ImpedanceVecd, Zero);
}

TEST_CASE("sva function results can be formatted with fmt", "[fmt][sva]") {
  check_fmt_nonempty("sva::RotX", sva::RotX(mc_rtc::constants::PI / 2));
  check_fmt_nonempty("sva::RotY", sva::RotY(mc_rtc::constants::PI / 2));
  check_fmt_nonempty("sva::RotZ", sva::RotZ(mc_rtc::constants::PI / 2));
}
