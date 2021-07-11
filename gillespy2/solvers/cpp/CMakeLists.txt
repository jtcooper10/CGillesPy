cmake_minimum_required(VERSION 3.18)
project(GillesPy2)

add_library(
	GillesPyCModel STATIC
	model.cpp
)

add_library(
	Sundials STATIC
	Sundials/src/cvode_nls.c
	Sundials/src/cvode_io.c
	Sundials/src/sundials_iterative.c
	Sundials/src/cvode_proj.c
	Sundials/src/sundials_matrix.c
	Sundials/src/sunmatrix_band.c
	Sundials/src/sunmatrix_dense.c
	Sundials/src/cvode_ls.c
	Sundials/src/sundials_linearsolver.c
	Sundials/src/sundials_nonlinearsolver.c
	Sundials/src/sundials_nvector_senswrapper.c
	Sundials/src/sunnonlinsol_newton.c
	Sundials/src/sundials_nvector.c
	Sundials/src/nvector_serial.c
	Sundials/src/cvode.c
	Sundials/src/cvode_spils.c
	Sundials/src/sundials_math.c
	Sundials/src/sunlinsol_spgmr.c
)
target_include_directories(
	Sundials PRIVATE
	Sundials/include
	Sundials/src
)

add_library(
	GillesPyCSolver SHARED
	model.cpp
	model.h
	template/template.cpp
	template/template.h
	template/template_defaults.h
	template/template_definitions.h
	ode_cpp_solver/ODESolver.cpp
	ode_cpp_solver/ODESolver.h
	ssa_cpp_solver/SSASolver.cpp
	ssa_cpp_solver/SSASolver.h
	tau_leaping_cpp_solver/TauLeapingSolver.cpp
	tau_leaping_cpp_solver/TauLeapingSolver.h
)
target_include_directories(
	GillesPyCSolver PUBLIC
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/template
	${CMAKE_SOURCE_DIR}/Sundials/include
	${CMAKE_SOURCE_DIR}/Sundials/src
)
target_link_libraries(GillesPyCSolver
	Sundials)
