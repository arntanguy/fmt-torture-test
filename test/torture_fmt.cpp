#include <catch2/catch_test_macros.hpp>
#include <fmt_formatters.h>
#include <SpaceVecAlg/PTransform.h>
#include <Eigen/Core>
#include <fmt/format.h>

/**
  fmt version summary:
  Ubuntu 20.04 (Focal)	6.1.2
  Ubuntu 22.04 (Jammy)	8.1.1
  Ubuntu 24.04 (Noble)	9.1.0
*/

TEST_CASE("Eigen types can be formatted with fmt", "[fmt][eigen]") {
  Eigen::Vector3d v(1.0, 2.0, 3.0);
  Eigen::Matrix3d m = Eigen::Matrix3d::Identity();

  // Just check that formatting compiles
  std::string v_str = fmt::format("Vector: {}", v);
  std::string m_str = fmt::format("Matrix:\n{}", m);

  REQUIRE_FALSE(v_str.empty());
  REQUIRE_FALSE(m_str.empty());

  // Test mc_log_ui
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
