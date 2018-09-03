#include "pch.h"
#include "core/search_engine.h"
#include <algorithm>

namespace Core::Search::Test
{
    using ::std::vector;
    using ::std::string;

    class SearchTest : public ::testing::Test
    {
    protected:
        virtual void SetUp() override final
        {
            search_init(
                "C:/Work/Dict/db/mat/",
                "ru_de_dict.db");
        }
 
    };

    TEST_F(SearchTest, SarchForExistingWordShouldFillTheResultDb) {
        search_for("Test");
        vector<string> results = search_get_result();
        ASSERT_TRUE(results.cend() != ::std::find(results.cbegin(), results.cend(), "Test"));
    }
}