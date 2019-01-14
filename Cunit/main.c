/*
 cc     essaicunit.c   -o essaicunit -I /usr/local/Cellar/cunit/2.1-3/include/ -lCUnit -L /usr/local/Cellar/cunit/2.1-3/lib/
 */

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include"../src/board.h" 

void test_FIb_new()
    {
        FIboard res;
        res = FIb_new(2);
        CU_ASSERT(
            res.colors[0][0]=='\0' &&
            res.colors[1][0]=='\0' &&
            res.colors[0][1]=='\0' &&
            res.colors[1][1]=='\0'
        );
        CU_ASSERT(res.size == 2);
    }
    
void test_FIb_init(void){
    FIboard res = FIb_new(2);
    FIb_init(&res);
    CU_ASSERT(
            res.colors[0][0]!='\0' &&
            res.colors[1][0]!='\0' &&
            res.colors[0][1]!='\0' &&
            res.colors[1][1]!='\0'
        );
}

void test_Fib_destroy(void){
    FIboard res = FIb_new(2);
    FIb_destroy(&res);
    CU_ASSERT(res.size==0);
}

void test_FIb_loadfromfile(void){
    FIboard res = FIb_new(2);
    FIb_loadfromfile(&res,"resources/FLOODLOAD.txt");
    CU_ASSERT(
        res.colors[0][0]=='R'&& 
        res.colors[0][1]=='B' &&
        res.colors[0][2]=='V' &&
        res.colors[1][0]=='J' &&
        res.colors[1][1]=='M' &&
        res.colors[1][2]=='G' &&
        res.colors[2][0]=='B' &&
        res.colors[2][1]=='V' &&
        res.colors[2][2]=='R'
    );
}

void test_FIb_connectedcomp(void){
    FIboard board = FIb_new(2);
    board.colors[0][0] = 'B';
    board.colors[1][0] = 'V';
    board.colors[0][1] = 'B';
    board.colors[1][1] = 'B';
    
    /*FIb_display(&board);*/
    
    FIboard res = FIb_connectedcomp(&board);
    /*FIb_display(&res);*/
    CU_ASSERT(
        res.colors[0][0]=='C' &&
        res.colors[1][0]=='\0' &&
        res.colors[0][1]=='C' &&
        res.colors[1][1]=='C'
    );
    
}

void test_FIb_color(void){
    FIboard board = FIb_new(1);
    FIb_color(&board,0,0,'V');
    CU_ASSERT(board.colors[0][0]=='V');
}

void test_FIb_colorcomp(void){
    FIboard board = FIb_new(2);
    board.colors[0][0] = 'J';
    board.colors[1][0] = 'V';
    board.colors[0][1] = 'J';
    board.colors[1][1] = 'V';
    FIboard compo = FIb_connectedcomp(&board);
    FIb_colorcomp(&board,&compo,'B');
    CU_ASSERT(board.colors[0][0]=='B' &&
    board.colors[0][1]=='B'
    );
}

void test_FIb_win(void){
    FIboard res = FIb_new(2);
    res.colors[0][0] = 'J';
    res.colors[1][0] = 'J';
    res.colors[0][1] = 'J';
    res.colors[1][1] = 'J';
    CU_ASSERT(FIb_win(res)==1);
    FIboard board = FIb_new(2);
    board.colors[0][0] = 'J';
    board.colors[1][0] = 'V';
    board.colors[0][1] = 'J';
    board.colors[1][1] = 'J';
    CU_ASSERT(FIb_win(board)==0);
}

void test_char_aleat() {
    char c = char_aleat();
    CU_ASSERT(c=='G' || c=='R' || c=='B' || c=='V' || c=='R' || c=='J' || c=='M');
}

/**/

int main() {
	CU_pSuite pSuite = NULL;
	
	if (CU_initialize_registry() != CUE_SUCCESS) {
		return CU_get_error();
	}
    
    pSuite = CU_add_suite("Utils",NULL,NULL);
    	
    if (CU_add_test (pSuite, "test of char_aleat",test_char_aleat)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

	pSuite = CU_add_suite("Board",NULL,NULL);

	if (pSuite==NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

    if (CU_add_test (pSuite, "test of Fib_new",test_FIb_new)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test (pSuite, "test of Fib_destroy",test_Fib_destroy)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test (pSuite, "test of Fib_init",test_FIb_init)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test (pSuite, "test of Fib_color",test_FIb_color)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test (pSuite, "test of Fib_connectedcomp",test_FIb_connectedcomp)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    
    if (CU_add_test (pSuite, "test of Fib_colorcomp",test_FIb_colorcomp)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    
    if (CU_add_test (pSuite, "test of Fib_loadfromfile",test_FIb_loadfromfile)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (CU_add_test (pSuite, "test of Fib_win",test_FIb_win)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    

    
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
	return 0;
}
