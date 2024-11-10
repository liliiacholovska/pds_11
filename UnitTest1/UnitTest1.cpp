#include "pch.h"
#include "CppUnitTest.h"
#include "../pds_11/pds_11.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestFloydWarshall)
        {
            int dist[MAX_N][MAX_N], next[MAX_N][MAX_N];
            int n = 4;

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    dist[i][j] = (i == j) ? 0 : INF;
                    next[i][j] = (i == j) ? i : -1;
                }
            }

            dist[0][2] = 3; next[0][1] = 1;
            dist[0][2] = 2; next[0][2] = 2;
            dist[1][3] = 5; next[1][3] = 3;
            dist[2][3] = 4; next[2][3] = 3;

            floydWarshall(n, dist, next);

            Assert::AreEqual(0, dist[0][0]);
            Assert::AreEqual(2147483647, dist[0][1]);
            Assert::AreEqual(2, dist[0][2]);
            Assert::AreEqual(6, dist[0][3]);

            Assert::AreEqual(INF, dist[1][0]);
            Assert::AreEqual(0, dist[1][1]);
            Assert::AreEqual(INF, dist[1][2]);
            Assert::AreEqual(5, dist[1][3]);

            Assert::AreEqual(INF, dist[2][0]);
            Assert::AreEqual(INF, dist[2][1]);
            Assert::AreEqual(0, dist[2][2]);
            Assert::AreEqual(4, dist[2][3]);

            Assert::AreEqual(INF, dist[3][0]);
            Assert::AreEqual(INF, dist[3][1]);
            Assert::AreEqual(INF, dist[3][2]);
            Assert::AreEqual(0, dist[3][3]);

            Assert::AreEqual(2, next[0][3]); 
            Assert::AreEqual(2, next[0][2]); 
        }
	};
}
