#include <Expected.h>
#include <algorithm>
#include <filesystem>
#include <format>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ranges>
#include <vector>

// https://devblogs.microsoft.com/cppblog/cpp23s-optional-and-expected/

namespace test_expected {

    static std::expected< void, int > SuccessOrError( bool success )
    {
        if( !success ) {
            return std::unexpected< int > { 3 };
        }

        return {};
    }

    enum class Status {
        Ok,
        AccessDenied,
        DataSourceError,
        DataError,
    };

    // enum class Status : unsigned long {}

    bool HasAcccess()
    {
        return true;
    }
    int OpenConnection()
    {
        return 0;
    }
    int Fetch()
    {
        return 0;
    }

    Status ReadData( std::vector< int > &data )
    {
        if( !HasAcccess() )
            return Status::AccessDenied;
        if( OpenConnection() != 0 )
            return Status::DataSourceError;
        if( Fetch() != 0 )
            return Status::DataError;
        data.push_back( 42 );
        return Status::Ok;
    }

    void print_value( int const v )
    {
        std::cout << v << '\n';
    }

    std::expected< std::vector< int >, Status > ReadData()
    {
        if( !HasAcccess() )
            return std::unexpected< Status > { Status::AccessDenied };
        if( OpenConnection() != 0 )
            return std::unexpected< Status > { Status::DataSourceError };
        if( Fetch() != 0 )
            return std::unexpected< Status > { Status::DataError };
        std::vector< int > data;
        data.push_back( 42 );
        return data;
    }

    TEST( test_expected, TestNameX )
    {
        auto result = ReadData();
        if( result ) {
            std::ranges::for_each( result.value(), print_value );
        } else {
            std::cout << std::format( "Error code: {}\n", ( int ) result.error() );
        }
    }

    TEST( test_expected, value_or )
    {
        std::vector< int > data;
        data.push_back( 42 );

        auto result = ReadData();

        result.value_or( data );
    }

    TEST( test_expected, success_or_error_success_case )
    {
        bool result = false;

        if( auto res = SuccessOrError( true ) )
            result = true;

        EXPECT_TRUE( result );
    }

    TEST( test_expected, success_or_error_success_case_void )
    {
        bool result = false;

        if( SuccessOrError( true ) )
            result = true;

        EXPECT_TRUE( result );
    }

    TEST( test_expected, success_or_error_fail_case )
    {
        bool result = false;

        if( auto res = SuccessOrError( false ) ) {
            result = false;
        } else {
            result = true;

            EXPECT_EQ( res.error(), 3 );
        }

        EXPECT_TRUE( result );
    }

    TEST( test_expected, expected_string )
    {
        std::expected< std::string, bool > expected = "testing";

        EXPECT_EQ( expected.value(), "testing" );
        EXPECT_EQ( *expected, "testing" );

        auto taken = *std::move( expected );

        EXPECT_EQ( taken, "testing" );

        EXPECT_EQ( expected.value(), "" );
        EXPECT_EQ( *expected, "" );
    }

    TEST( test_expected, expected_unique_ptr )
    {
        auto unique_string = std::make_unique< std::string >( "testing" );

        std::expected< std::unique_ptr< std::string >, bool > expected = std::move( unique_string );

        EXPECT_EQ( *expected.value().get(), "testing" );
        EXPECT_EQ( *expected.value(), "testing" );

        auto taken = *std::move( expected );

        EXPECT_EQ( *taken, "testing" );

        EXPECT_EQ( expected.value(), nullptr );
        EXPECT_EQ( *expected, nullptr );
    }

}
