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
        pybind11::arg("effectedState") = -1, pybind11::arg("collapseTo") = false)
        .def_readwrite("ConstraintType", &Constraint::ConstraintType)
        .def_readwrite("offsets", &Constraint::offsets)
        .def_readwrite("effectedState", &Constraint::effectedState)
        .def_readwrite("collapseTo", &Constraint::collapseTo);
        
    pybind11::class_<WaveCollapse, std::shared_ptr<WaveCollapse>>(m, "WaveCollapse")
        .def(pybind11::init([](std::vector<float> STDStates, std::vector<Constraint> constraints, int chunkSize, int initCollapse) {
            return std::make_shared<WaveCollapse>(STDStates, constraints, chunkSize, initCollapse);
        }), pybind11::arg("STDStates") = std::vector<float>(), pybind11::arg("constraints") = std::vector<Constraint>(), 
        pybind11::arg("chunkSize"), pybind11::arg("initCollapse") = -1)
        .def("generateChunk", &WaveCollapse::GenerateChunk)
        .def("containsChunk", &WaveCollapse::containsChunk)
        .def("collapseChunk", (void (WaveCollapse::*)(int, int)) &WaveCollapse::collapseChunk)
        .def("collapseChunk", (void (WaveCollapse::*)(std::shared_ptr<Chunk>)) &WaveCollapse::collapseChunk)
        .def("setSeed", &WaveCollapse::setSeed)
        .def("getChunk", &WaveCollapse::getChunk)
        .def("getChunkSize", &WaveCollapse::getChunkSize);

    pybind11::class_<Chunk, std::shared_ptr<Chunk>>(m, "Chunk")
        .def(pybind11::init<int, int, int, std::vector<float>, const std::vector<Constraint>&, int>())
        .def("collapse", &Chunk::collapse)
        .def("getTile", &Chunk::getTile)
        .def("getSize", &Chunk::getSize)
        .def("getLocation", &Chunk::getLocation)
        .def("getState", &Chunk::getState)
        .def("getCollapse", &Chunk::getCollapse);
        

    pybind11::class_<Tile, std::shared_ptr<Tile>>(m, "Tile")
    .def(pybind11::init([](std::vector<float> state) {
        return std::make_shared<Tile>(state);
    }), pybind11::arg("state") = std::vector<float>())
    .def_readwrite("state", &Tile::state)
    .def_readwrite("collapsed", &Tile::collapsed)
    .def_readwrite("collapsedState", &Tile::collapsedState);
    
    
}
