# the usual boilerplate setup
cmake_minimum_required(VERSION 3.1)
project(tests LANGUAGES CXX)

# tell CMake to use CTest extension
enable_testing()

# create an executables for each algorithm
add_executable(1_SingleResponsibilityPrinciple SingleResponsibilityPrinciple.cxx)
add_executable(2_OpenClosedPrinciple OpenClosedPrinciple.cxx)
add_executable(3_LiskovSubstitutionPrinciple_FactoryPattern LiskovSubstitutionPrinciple_FactoryPattern.cxx)
add_executable(4_InterfaceSegregationPrinciple InterfaceSegregationPrinciple.cxx)
add_executable(5_DependencyInversionPrinciple DependencyInversionPrinciple.cxx)

# register test CTest
add_test(NAME Single_Responsibility_Principle COMMAND 1_SingleResponsibilityPrinciple)
add_test(NAME Open_Closed_Principle           COMMAND 2_OpenClosedPrinciple)
add_test(NAME Liskov_Substitution_Principle_FactoryPattern   COMMAND 3_LiskovSubstitutionPrinciple_FactoryPattern)
add_test(NAME Interface_Segregation_Principle COMMAND 4_InterfaceSegregationPrinciple)
add_test(NAME Dependency_Inversion_Principle  COMMAND 5_DependencyInversionPrinciple)
