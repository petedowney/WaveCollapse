/**
 * @file WaveCollapseInt.cpp
 * @brief Implementation of the Wave Collapse Algorithm interface for Python bindings.
 *
 * This file contains the implementation of the Wave Collapse Algorithm interface
 * for Python bindings. It defines the necessary classes and functions to expose
 * the Wave Collapse Algorithm to Python.
 */
//
// Created by Pete Downey on 4/13/24.
//

#define PY_SSIZE_T_CLEAN
//#include <Python.h>
//#include <structmember.h>
#include "pybind11/pybind11.h"
#include "WaveCollapseInt.h"

#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

#include <vector>
#include <unordered_map>
#include <tuple>

#include "WaveCollapse.h"

PYBIND11_MODULE(WaveCollapseInterface, m) {
    m.doc() = "Wave Collapse Algorithm";

    pybind11::enum_<Type>(m, "Type")
        .value("CORD", Type::CORD)
        .value("RADIUS", Type::RADIUS)
        .value("SQUARE", Type::SQUARE)
        .export_values();

    pybind11::class_<Constraint>(m, "Constraint")
        .def(pybind11::init([](Type ConstraintType, std::vector<std::tuple<int, int, int>> offsets, int effectedState, bool collapseTo) {
            return Constraint{ConstraintType, offsets, effectedState, collapseTo};
        }), pybind11::arg("ConstraintType") = Type::CORD, pybind11::arg("offsets") = std::vector<std::tuple<int, int, int>>(),
        pybind11::arg("effectedState") = -1, pybind11::arg("collapseTo") = false, "The constructor for the Constraint class.")
        .def_readwrite("ConstraintType", &Constraint::ConstraintType, "The type of constraint.")
        .def_readwrite("offsets", &Constraint::offsets, "The offsets of the constraint.")
        .def_readwrite("effectedState", &Constraint::effectedState, "The state that gets collapsed.")
        .def_readwrite("collapseTo", &Constraint::collapseTo, "Whether to collapse to the state or away from the state.");
        
    pybind11::class_<WaveCollapse, std::shared_ptr<WaveCollapse>>(m, "WaveCollapse")
        .def(pybind11::init([](std::vector<float> STDStates, std::vector<Constraint> constraints, int chunkSize, int initCollapse) {
            return std::make_shared<WaveCollapse>(STDStates, constraints, chunkSize, initCollapse);
        }), pybind11::arg("STDStates") = std::vector<float>(), pybind11::arg("constraints") = std::vector<Constraint>(), 
        pybind11::arg("chunkSize"), pybind11::arg("initCollapse") = -1, "The constructor for the WaveCollapse class.")
        .def("generateChunk", &WaveCollapse::GenerateChunk, "Generates a new chunk based on the current state of the WaveCollapse object.")
        .def("containsChunk", &WaveCollapse::containsChunk, "Checks if a chunk with the given coordinates exists in the WaveCollapse object.")
        .def("collapseChunk", (void (WaveCollapse::*)(int, int)) &WaveCollapse::collapseChunk, "Collapses the chunk at the given coordinates.")
        .def("collapseChunk", (void (WaveCollapse::*)(std::shared_ptr<Chunk>)) &WaveCollapse::collapseChunk, "Collapses the given chunk.")
        .def("setSeed", &WaveCollapse::setSeed, "Sets the seed for the random number generator used by the WaveCollapse object.")
        .def("getChunk", &WaveCollapse::getChunk, "Gets the chunk at the given coordinates.")
        .def("getChunkSize", &WaveCollapse::getChunkSize, "Gets the size of each chunk in the WaveCollapse object.");

    pybind11::class_<Chunk, std::shared_ptr<Chunk>>(m, "Chunk")
        .def(pybind11::init<int, int, int, std::vector<float>, const std::vector<Constraint>&, int>(), pybind11::arg("x"), pybind11::arg("y"), pybind11::arg("z"), pybind11::arg("states"), pybind11::arg("constraints"), pybind11::arg("collapseState"), "The constructor for the Chunk class.")
        .def("collapse", &Chunk::collapse, "Collapses the chunk based on the constraints and neighboring chunks.")
        .def("getTile", &Chunk::getTile, "Gets the tile at the given coordinates within the chunk.")
        .def("getSize", &Chunk::getSize, "Gets the size of the chunk.")
        .def("getLocation", &Chunk::getLocation, "Gets the location of the chunk.")
        .def("getState", &Chunk::getState, "Gets the state of the chunk.")
        .def("getCollapse", &Chunk::getCollapse, "Gets the collapse state of the chunk.");
        

    pybind11::class_<Tile, std::shared_ptr<Tile>>(m, "Tile")
    .def(pybind11::init([](std::vector<float> state) {
        return std::make_shared<Tile>(state);
    }), pybind11::arg("state") = std::vector<float>(), "The constructor for the Tile class.")
    .def_readwrite("state", &Tile::state, "The state of the tile.")
    .def_readwrite("collapsed", &Tile::collapsed, "Whether the tile has collapsed.")
    .def_readwrite("collapsedState", &Tile::collapsedState, "The collapsed state of the tile if it has collapsed. -1 if not");
    
    
}
