#ifndef H7E147A58_B997_4DC5_B6EB_A014CC6F6C3E
#define H7E147A58_B997_4DC5_B6EB_A014CC6F6C3E

#include <cub/utils/SourceFile.h>
#include <cub/mem/ScopeExit.h>
#include <hamcrest/base/Matcher.h>
#include <hamcrest/base/Description.h>
#include <cut/except/AssertionError.h>

CUT_NS_BEGIN

template <typename U, typename V>
void assert_that(const U& actual, hamcrest::Matcher<V>* matcher, const std::string& source)
{
    SCOPE_EXIT([=]{ delete matcher; });

    if (!matcher->matches(actual))
    {
        hamcrest::Description desc;
        
        desc.appendText("\nExpected: ")
            .appendDescriptionOf(*matcher)
            .appendText("\n     but: ");

        matcher->describeMismatch(actual, desc);

        throw AssertionError(source, desc.to_s());
    }
}

#define ASSERT_THAT(actual, matcher) \
    CUT_NS::assert_that(actual, matcher, FULL_FILE())

CUT_NS_END

#endif