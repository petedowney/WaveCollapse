//
// Created by Pete Downey on 4/13/24.
//

#define PY_SSIZE_T_CLEAN
//#include <Python.h>
//#include <structmember.h>
#include "pybind11/pybind11.h"
#include "WaveCollapseInterface.h"

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
        .export_values();

    pybind11::class_<Constraint>(m, "Constraint")
        .def(pybind11::init<Type, int, int, std::vector<int>>(), 
        pybind11::arg("ConstraintType") = Type::CORD, pybind11::arg("causingState") = 0, 
        pybind11::arg("effectedState") = 0, pybind11::arg("miscArgs") = std::vector<int>())
        
        .def_readwrite("ConstraintType", &Constraint::ConstraintType)
        .def_readwrite("causingState", &Constraint::causingState)
        .def_readwrite("effectedState", &Constraint::effectedState)
        .def_readwrite("miscArgs", &Constraint::miscArgs);

    pybind11::class_<WaveCollapse, std::shared_ptr<WaveCollapse>>(m, "WaveCollapse")
        .def(pybind11::init<std::vector<float>, std::vector<Constraint>, int>())
        .def("GenerateChunk", &WaveCollapse::GenerateChunk)
        .def("containsChunk", &WaveCollapse::containsChunk)
        .def("collapseChunk", (void (WaveCollapse::*)(int, int)) &WaveCollapse::collapseChunk)
        .def("collapseChunk", (void (WaveCollapse::*)(std::shared_ptr<Chunk>)) &WaveCollapse::collapseChunk)
        .def("setSeed", &WaveCollapse::setSeed)
        .def("getChunk", &WaveCollapse::getChunk)
        .def("getChunkSize", &WaveCollapse::getChunkSize);

    pybind11::class_<Chunk, std::shared_ptr<Chunk>>(m, "Chunk")
        .def(pybind11::init<int, int, int, std::vector<float>, const std::vector<Constraint>&>())
        .def("collapse", &Chunk::collapse)
        .def("getTile", &Chunk::getTile)
        .def("getCollapsedTileState", (int (Chunk::*)(int, int)) &Chunk::getCollapsedTileState)
        .def("getCollapsedTileState", (int (Chunk::*)(std::shared_ptr<Tile>)) &Chunk::getCollapsedTileState)
        .def("getSize", &Chunk::getSize)
        .def("getLocation", &Chunk::getLocation)
        .def("collapseTile", (void (Chunk::*)(int, int, int)) &Chunk::collapseTile)
        .def("collapseTile", (void (Chunk::*)(std::shared_ptr<Tile>, int)) &Chunk::collapseTile);

    pybind11::class_<Tile, std::shared_ptr<Tile>>(m, "Tile")
    .def(pybind11::init([](std::vector<float> state, bool collapsed) {
        return std::make_shared<Tile>(state, collapsed);
    }), pybind11::arg("state") = std::vector<float>(), pybind11::arg("collapsed") = false)
    .def_readwrite("state", &Tile::state)
    .def_readwrite("collapsed", &Tile::collapsed);
}
