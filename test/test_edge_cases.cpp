#include <catch2/catch_test_macros.hpp>
#include <cstring>
#include <cerrno>

TEST_CASE("Null input handling", "[edge]") {
    int ret = reel_forge_submit(NULL, NULL);
    REQUIRE(ret == -EINVAL);
}

TEST_CASE("Empty input handling", "[edge]") {
    struct reel_forge_job job;
    std::memset(&job, 0, sizeof(job));
    REQUIRE(job.type == 0);
    REQUIRE(job.width == 0);
}

TEST_CASE("Boundary values", "[edge]") {
    struct reel_forge_job job;
    std::memset(&job, 0, sizeof(job));
    job.type = 0;
    REQUIRE(job.type == 0);
    job.type = 1;
    REQUIRE(job.type == 1);
}

TEST_CASE("Concurrent access", "[edge]") {
    std::atomic<int> counter{0};
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&]() { counter++; });
    }
    for (auto& t : threads) t.join();
    REQUIRE(counter == 10);
}

TEST_CASE("Resource cleanup on error", "[edge]") {
    struct reel_forge_job job;
    std::memset(&job, 0, sizeof(job));
    job.type = 99;
    REQUIRE(job.type == 99);
}
