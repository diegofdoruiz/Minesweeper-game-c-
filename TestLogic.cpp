#define CATCH_CONFIG_MAIN
#include <vector>
#include "catch.hpp"
#include "Logic.hpp"

using namespace std;

Logic logic;

TEST_CASE( "setRows/1=1", "Prove that 1 equals 1" ){
    SECTION("setting the rows") {
	    INFO("Using setRows") // Only appears on a FAIL
	    logic.setRows(1);
	    CAPTURE(logic.getRows()); // Displays this variable on a FAIL
	    CHECK(logic.getRows() == 1);
	}
}

TEST_CASE("initParameters", "Validate parameters game"){
	//Chek init parameters por game
	SECTION("setting initParameters game"){
		INFO("Using initParameters")
		logic.initParameters("15 8 10");
		CAPTURE(logic.validateParameters());
		CHECK(logic.validateParameters() == true);
	}
}

TEST_CASE( "Assert that something is false (stops at first failure)", "[require-false]" ) {
    REQUIRE_FALSE( logic.getGameFinish() == true );
}

TEST_CASE( "initBoard", "Prove that endMessage is empty when init game" ) {
    //Chek init parameters por game
	SECTION("init board"){
		INFO("Using initBoar")
		logic.setRows(15);
		logic.setColumns(8);
		logic.setMines(10);
		CAPTURE(logic.getEndMessage());
		CHECK(logic.getEndMessage() == "");
	}
}

TEST_CASE( "builtVectorMinesPositions", "size vector" ) {
    //Chek init parameters por game
	SECTION("build mines positions vector"){
		INFO("Using builtVectorMinesPositions")
		logic.setRows(15);
		logic.setColumns(8);
		logic.setMines(10);
		logic.builtVectorMinesPositions();
		CAPTURE(logic.getMinesPosVector().size());
		CHECK(logic.getMinesPosVector().size() == 10);
	}
}

