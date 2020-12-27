#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <cstdlib>
#include <vector>

#include "game.h"
#include "user.h"
#include "cell.h"
#include "point.h"

namespace py = pybind11;

void initRandom(unsigned int seed) {
    srand(seed);
}

PYBIND11_MAKE_OPAQUE(std::set<User*>);

PYBIND11_MODULE(_game, m) {
    m.def("initRandom", &initRandom);
    py::class_<Game>(m, "Game", py::buffer_protocol())
    .def(py::init<>())
    .def("addUser", &Game::addUser)
    .def("tick", &Game::gameTick)
    .def("movePlayer", &Game::addMovePlayerEvent)
    .def_readwrite("foods", &Game::foods)
    .def_readwrite("users", &Game::users);

    py::class_<User, std::shared_ptr<User>>(m, "User", py::buffer_protocol())
    .def_readwrite("cells", &User::cells)
    .def_property("pos", &User::getPos, nullptr);

    py::class_<Cell, std::shared_ptr<Cell>>(m, "Cell", py::buffer_protocol())
    .def_property("pos", &Cell::getPos, nullptr)
    .def_property("radius", &Cell::getRadius, nullptr);

    py::class_<Point, std::shared_ptr<Point>>(m, "Point", py::buffer_protocol())
    .def(py::init<double, double>())
    .def("dist", &Point::dist)
    .def_property("x", &Point::getX, nullptr)
    .def_property("y", &Point::getY, nullptr);
}
