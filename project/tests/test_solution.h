#ifndef TEST_SOLUTION_H
#define TEST_SOLUTION_H

#include "minunt.h"
#include "../Solution.h"
#include "../Vertice.h"

#define MINUNIT_EPSILON 1E-4

void test_setup(void) {
}

void test_teardown(void) {
}

MU_TEST(solution_init) {
    Solution sol( 2, 7.5 );
	mu_assert_int_eq( sol.get_number_paths(), 2 );
    mu_assert_double_eq( sol.get_time_per_path(), 7.5 );
    mu_assert_double_eq( sol.get_total_rewards(), 0.0 );
    mu_assert_double_eq( sol.get_total_time(), 0.0 );
    mu_assert_int_eq( sol.get_rewards( 0 ), 0 );
    mu_assert_int_eq( sol.get_rewards( 1 ), 0 );
    mu_assert_double_eq( sol.get_time_path( 0 ), 0.0 );
    mu_assert_double_eq( sol.get_time_path( 1 ), 0.0 );
}

MU_TEST(solution_set_initial_and_final_vertice) {
    Vertice initial( 0.0, 0.0, 0 );
    Vertice final( 3.0, 4.0, 0 );
    Solution sol( 2, 7.5 );
    for( int i = 0; i < 2; i++ ){
        sol.add_initial_and_final_vertice( i, &initial, &final );
    }
    for( int i = 0; i < 2; i++ ){
        mu_assert_int_eq( sol.get_length_of_path( i ), 2 );
        mu_assert_double_eq( sol.get_time_path( i ), 5.0 );
        mu_assert_int_eq( sol.get_last_path_vertice_in_path( i )->get_hash(), final.get_hash() );
        mu_assert_int_eq( sol.get_rewards( i ), 0 );
    }
	mu_assert_int_eq( sol.get_number_paths(), 2 );
    mu_assert_double_eq( sol.get_time_per_path(), 7.5 );
    mu_assert_double_eq( sol.get_total_rewards(), 0.0 );
    mu_assert_double_eq( sol.get_total_time(), 10.0 );
}

MU_TEST(solution_set_initial_and_final_vertice_fail) {
    Vertice initial( 0.0, 0.0, 0 );
    Vertice final( 3.0, 4.0, 0 );
    Solution sol( 2, 7.5 );
    try{
        sol.add_initial_and_final_vertice( -1, &initial, &final );
        mu_fail("path invalid: -1");
    }catch(exception &e ){
    }
    try{
        sol.add_initial_and_final_vertice( 0, &initial, 0 );
        mu_fail("initial vertice is null");
    }catch(exception &e ){
    }
    try{
        sol.add_initial_and_final_vertice( 0, 0, &final );
        mu_fail("final vertice is null");
    }catch(exception &e ){
    }
    sol.add_initial_and_final_vertice( 0, &initial, &final );
    sol.add_initial_and_final_vertice( 1, &initial, &final );
    try{
        sol.add_initial_and_final_vertice( 2, &initial, &final );
        mu_fail("path is invalid: 2");
    }catch(exception &e ){
    }
    for( int i = 0; i < 2; i++ ){
        mu_assert_int_eq( sol.get_length_of_path( i ), 2 );
        mu_assert_double_eq( sol.get_time_path( i ), 5.0 );
        mu_assert_int_eq( sol.get_last_path_vertice_in_path( i )->get_hash(), final.get_hash() );
        mu_assert_int_eq( sol.get_rewards( i ), 0 );
    }
	mu_assert_int_eq( sol.get_number_paths(), 2 );
    mu_assert_double_eq( sol.get_time_per_path(), 7.5 );
    mu_assert_double_eq( sol.get_total_rewards(), 0.0 );
    mu_assert_double_eq( sol.get_total_time(), 10.0 );
}

MU_TEST(solution_set_initial_and_final_vertice_fail_2) {
    Vertice initial( 0.0, -7.0, 0 );
    Vertice final( 0.0, 7.0, 0 );
    Solution sol( 2, 13.3 );
    try{
        sol.add_initial_and_final_vertice( 0, &initial, &final );
        mu_fail("path length is bigger");
    }catch(exception &e ){
    }
    for( int i = 0; i < 2; i++ ){
        mu_assert_int_eq( sol.get_length_of_path( i ), 0 );
        mu_assert_double_eq( sol.get_time_path( i ), 0.0 );
        mu_assert_int_eq( sol.get_rewards( i ), 0 );
    }
	mu_assert_int_eq( sol.get_number_paths(), 2 );
    mu_assert_double_eq( sol.get_time_per_path(), 13.3 );
    mu_assert_double_eq( sol.get_total_rewards(), 0.0 );
    mu_assert_double_eq( sol.get_total_time(), 0.0 );
}

MU_TEST(solution_add_vertice_in_path) {
    Vertice initial( 0.0, 0.0, 0 );
    Vertice final( 3.0, 4.0, 0 );
    Vertice new_v( 6.0, 8.0, 5 );
    Solution sol( 2, 15.0 );
    for( int i = 0; i < 2; i++ ){
        sol.add_initial_and_final_vertice( i, &initial, &final );
    }
    bool result = sol.add( 0, &new_v );
    mu_check( result == true );
    mu_assert_int_eq( sol.get_length_of_path( 0 ), 3 );
    mu_assert_double_eq( sol.get_time_path( 0 ), 15.0 );
    mu_assert_int_eq( sol.get_last_path_vertice_in_path( 0 )->get_hash(), final.get_hash() );
    mu_assert_int_eq( sol.get_rewards( 0 ), 5 );

    mu_assert_int_eq( sol.get_length_of_path( 1 ), 2 );
    mu_assert_double_eq( sol.get_time_path( 1 ), 5.0 );
    mu_assert_int_eq( sol.get_last_path_vertice_in_path( 1 )->get_hash(), final.get_hash() );
    mu_assert_int_eq( sol.get_rewards( 1 ), 0 );

	mu_assert_int_eq( sol.get_number_paths(), 2 );
    mu_assert_double_eq( sol.get_time_per_path(), 15.0 );
    mu_assert_double_eq( sol.get_total_rewards(), 5.0 );
    mu_assert_double_eq( sol.get_total_time(), 20.0 );
}

MU_TEST(solution_add_vertice_in_path_fail) {
    Vertice initial( 0.0, 0.0, 0 );
    Vertice final( 3.0, 4.0, 0 );
    Vertice new_v( 6.0, 8.0, 5 );
    Solution sol( 2, 7.5 );
    for( int i = 0; i < 2; i++ ){
        sol.add_initial_and_final_vertice( i, &initial, &final );
    }
    bool result = sol.add( 2, &new_v );// path invalid
    mu_check( result == false );
    result = sol.add( 2, 0 ); // vertice null
    mu_check( result == false );
    result = sol.add( 1, &new_v ); // time restriction
    mu_check( result == false );
    mu_assert_int_eq( sol.get_length_of_path( 0 ), 2 );
    mu_assert_double_eq( sol.get_time_path( 0 ), 5.0 );
    mu_assert_int_eq( sol.get_last_path_vertice_in_path( 0 )->get_hash(), final.get_hash() );
    mu_assert_double_eq( sol.get_rewards( 0 ), 0.0 );

    mu_assert_int_eq( sol.get_length_of_path( 1 ), 2 );
    mu_assert_double_eq( sol.get_time_path( 1 ), 5.0 );
    mu_assert_int_eq( sol.get_last_path_vertice_in_path( 1 )->get_hash(), final.get_hash() );
    mu_assert_double_eq( sol.get_rewards( 1 ), 0.0 );

	mu_assert_int_eq( sol.get_number_paths(), 2 );
    mu_assert_double_eq( sol.get_time_per_path(), 7.5 );
    mu_assert_double_eq( sol.get_total_rewards(), 0.0 );
    mu_assert_double_eq( sol.get_total_time(), 10.0 );
}

MU_TEST(solution_move_sucess){
    Vertice initial( 1.0, 1.0, 0 );
    Vertice final( 2.0, 2.0, 0 );
    Vertice v1( 2.3, 4.5, 1 );
    Vertice v2( 1.8, 2.1, 2 );
    Vertice v3( 2.2, 3.3, 4 );
    Vertice v4( 2.7, 3.1, 8 );
    Solution sol( 2, 9.0 );
    for( int i = 0; i < 2; i++ ){
        sol.add_initial_and_final_vertice( i, &initial, &final );
    }
    sol.add( 0, &v1 );
    sol.add( 0, &v2 );
    sol.add( 1, &v3 );
    sol.add( 1, &v4 );
    bool result = sol.move( 1, 2, 0, 3 );
    mu_check( result == true );
    mu_assert_int_eq( sol.get_length_of_path( 0 ), 5 );
    mu_assert_double_eq( 8.8343, sol.get_time_path( 0 ) );
    mu_assert_int_eq( sol.get_rewards( 0 ), 11 );

    mu_assert_int_eq( sol.get_length_of_path( 1 ), 3 );
    mu_assert_double_eq( sol.get_time_path( 1 ), 3.9095 );
    mu_assert_int_eq( sol.get_rewards( 1 ), 4 );

	mu_assert_int_eq( sol.get_number_paths(), 2 );
    mu_assert_double_eq( sol.get_time_per_path(), 9.0 );
    mu_assert_double_eq( sol.get_total_rewards(), 15.0 );
    mu_assert_double_eq( sol.get_total_time(), 12.7438 );
}

MU_TEST(solution_move_sucess_fail){
    Vertice initial( 1.0, 1.0, 0 );
    Vertice final( 2.0, 2.0, 0 );
    Vertice v1( 2.3, 4.5, 1 );
    Vertice v2( 1.8, 2.1, 2 );
    Vertice v3( 2.2, 3.3, 4 );
    Vertice v4( 2.7, 3.1, 8 );
    Solution sol( 2, 7.0 );
    for( int i = 0; i < 2; i++ ){
        sol.add_initial_and_final_vertice( i, &initial, &final );
    }
    sol.add( 0, &v1 );
    sol.add( 0, &v2 );
    sol.add( 1, &v3 );
    sol.add( 1, &v4 );
    bool result = sol.move( 1, 2, 0, 3 );
    mu_check( result == false );
    mu_assert_int_eq( sol.get_length_of_path( 0 ), 4 );
    mu_assert_double_eq( sol.get_time_path( 0 ), 6.4087 );
    mu_assert_int_eq( sol.get_rewards( 0 ), 3 );

    mu_assert_int_eq( sol.get_length_of_path( 1 ), 4 );
    mu_assert_double_eq( sol.get_time_path( 1 ), 4.4365 );
    mu_assert_int_eq( sol.get_rewards( 1 ), 12 );

	mu_assert_int_eq( sol.get_number_paths(), 2 );
    mu_assert_double_eq( sol.get_time_per_path(), 7.0 );
    mu_assert_double_eq( sol.get_total_rewards(), 15.0 );
    mu_assert_double_eq( sol.get_total_time(), 10.8453 ); 
}

MU_TEST(solution_move_sucess_fail_2){
    Vertice initial( 1.0, 1.0, 0 );
    Vertice final( 2.0, 2.0, 0 );
    Vertice v1( 2.3, 4.5, 1 );
    Vertice v2( 1.8, 2.1, 2 );
    Vertice v3( 2.2, 3.3, 4 );
    Vertice v4( 2.7, 3.1, 8 );
    Solution sol( 2, 7.0 );
    for( int i = 0; i < 2; i++ ){
        sol.add_initial_and_final_vertice( i, &initial, &final );
    }
    sol.add( 0, &v1 );
    sol.add( 0, &v2 );
    sol.add( 1, &v3 );
    sol.add( 1, &v4 );
    bool result = sol.move( 1, 2, 0, 4 );
    mu_check( result == false );
    result = sol.move( 1, 0, 0, 3 );
    mu_check( result == false );
    result = sol.move( 1, -2, 0, 3 );
    mu_check( result == false );
    mu_assert_int_eq( sol.get_length_of_path( 0 ), 4 );
    mu_assert_double_eq( sol.get_time_path( 0 ), 6.4087 );
    mu_assert_int_eq( sol.get_rewards( 0 ), 3 );

    mu_assert_int_eq( sol.get_length_of_path( 1 ), 4 );
    mu_assert_double_eq( sol.get_time_path( 1 ), 4.4365 );
    mu_assert_int_eq( sol.get_rewards( 1 ), 12 );

	mu_assert_int_eq( sol.get_number_paths(), 2 );
    mu_assert_double_eq( sol.get_time_per_path(), 7.0 );
    mu_assert_double_eq( sol.get_total_rewards(), 15.0 );
    mu_assert_double_eq( sol.get_total_time(), 10.8453 ); 
}

MU_TEST(solution_swap_sucess){
    Vertice initial( 1.0, 1.0, 0 );
    Vertice final( 2.0, 2.0, 0 );
    Vertice v1( 2.3, 4.5, 1 );
    Vertice v2( 1.8, 2.1, 2 );
    Vertice v3( 2.2, 3.3, 4 );
    Vertice v4( 2.7, 3.1, 8 );
    Solution sol( 2, 7.0 );
    for( int i = 0; i < 2; i++ ){
        sol.add_initial_and_final_vertice( i, &initial, &final );
    }
    sol.add( 0, &v1 );
    sol.add( 0, &v2 );
    sol.add( 1, &v3 );
    sol.add( 1, &v4 );
    bool result = sol.swap( 1, 2, 0, 1 );
    mu_check( result == true );
    mu_assert_int_eq( sol.get_length_of_path( 0 ), 4 );
    mu_assert_double_eq( sol.get_time_path( 0 ), 4.2708 );
    mu_assert_int_eq( sol.get_rewards( 0 ), 10 );

    mu_assert_int_eq( sol.get_length_of_path( 1 ), 4 );
    mu_assert_double_eq( sol.get_time_path( 1 ), 6.3163 );
    mu_assert_int_eq( sol.get_rewards( 1 ), 5 );

	mu_assert_int_eq( sol.get_number_paths(), 2 );
    mu_assert_double_eq( sol.get_time_per_path(), 7.0 );
    mu_assert_double_eq( sol.get_total_rewards(), 15.0 );
    mu_assert_double_eq( sol.get_total_time(), 10.5871 );
}

MU_TEST(solution_swap_fail){
    Vertice initial( 1.0, 1.0, 0 );
    Vertice final( 2.0, 2.0, 0 );
    Vertice v1( 2.3, 4.5, 1 );
    Vertice v2( 2.2, 3.3, 2 );
    Vertice v3( 1.8, 2.1, 4 );
    Vertice v4( 2.7, 3.1, 8 );
    Solution sol( 2, 6.3 );
    for( int i = 0; i < 2; i++ ){
        sol.add_initial_and_final_vertice( i, &initial, &final );
    }
    sol.add( 0, &v1 );
    sol.add( 0, &v2 );
    sol.add( 1, &v3 );
    sol.add( 1, &v4 );
    bool result = sol.swap( 1, 2, 0, 3 );
    mu_check( result == false );
    mu_assert_int_eq( sol.get_length_of_path( 0 ), 4 );
    mu_assert_double_eq( sol.get_time_path( 0 ), 6.2530 );
    mu_assert_int_eq( sol.get_rewards( 0 ), 3 );

    mu_assert_int_eq( sol.get_length_of_path( 1 ), 4 );
    mu_assert_double_eq( sol.get_time_path( 1 ), 4.0093 );
    mu_assert_int_eq( sol.get_rewards( 1 ), 12 );

	mu_assert_int_eq( sol.get_number_paths(), 2 );
    mu_assert_double_eq( sol.get_time_per_path(), 6.3 );
    mu_assert_double_eq( sol.get_total_rewards(), 15.0 );
    mu_assert_double_eq( sol.get_total_time(), 10.2624 ); 
}

MU_TEST(solution_swap_fail_2){
    Vertice initial( 1.0, 1.0, 0 );
    Vertice final( 2.0, 2.0, 0 );
    Vertice v1( 2.3, 4.5, 1 );
    Vertice v2( 1.8, 2.1, 2 );
    Vertice v3( 2.2, 3.3, 4 );
    Vertice v4( 2.7, 3.1, 8 );
    Solution sol( 2, 7.0 );
    for( int i = 0; i < 2; i++ ){
        sol.add_initial_and_final_vertice( i, &initial, &final );
    }
    sol.add( 0, &v1 );
    sol.add( 0, &v2 );
    sol.add( 1, &v3 );
    sol.add( 1, &v4 );
    bool result = sol.swap( 1, 2, 0, 3 );
    mu_check( result == false );
    result = sol.swap( 1, 0, 0, 3 );
    mu_check( result == false );
    result = sol.swap( 1, -2, 0, 3 );
    mu_check( result == false );
    mu_assert_int_eq( sol.get_length_of_path( 0 ), 4 );
    mu_assert_double_eq( sol.get_time_path( 0 ), 6.4087 );
    mu_assert_int_eq( sol.get_rewards( 0 ), 3 );

    mu_assert_int_eq( sol.get_length_of_path( 1 ), 4 );
    mu_assert_double_eq( sol.get_time_path( 1 ), 4.4365 );
    mu_assert_int_eq( sol.get_rewards( 1 ), 12 );

	mu_assert_int_eq( sol.get_number_paths(), 2 );
    mu_assert_double_eq( sol.get_time_per_path(), 7.0 );
    mu_assert_double_eq( sol.get_total_rewards(), 15.0 );
    mu_assert_double_eq( sol.get_total_time(), 10.8453 ); 
}

MU_TEST_SUITE(test_suite_solution) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(solution_init);
    MU_RUN_TEST(solution_set_initial_and_final_vertice);
    MU_RUN_TEST(solution_set_initial_and_final_vertice_fail);
    MU_RUN_TEST( solution_set_initial_and_final_vertice_fail_2 );
    MU_RUN_TEST(solution_add_vertice_in_path);
    MU_RUN_TEST(solution_add_vertice_in_path_fail);
    MU_RUN_TEST(solution_move_sucess);
    MU_RUN_TEST( solution_move_sucess_fail );
    MU_RUN_TEST( solution_move_sucess_fail_2 );
    MU_RUN_TEST( solution_swap_sucess );
    MU_RUN_TEST( solution_swap_fail );
    MU_RUN_TEST( solution_swap_fail_2 );
}

#endif