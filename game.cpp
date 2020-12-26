#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <vector>

#include "game.h"
#include "user.h"
#include "cell.h"
#include "point.h"

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::set<User*>);

PYBIND11_MODULE(_game, m) {
    py::class_<Game>(m, "Game", py::buffer_protocol())
    .def(py::init<>())
    .def("addUser", &Game::addUser)
    .def_readwrite("foods", &Game::foods)
    .def_readwrite("users", &Game::users);

    py::class_<User, std::shared_ptr<User>>(m, "User", py::buffer_protocol());

    py::class_<Cell, std::shared_ptr<Cell>>(m, "Cell", py::buffer_protocol())
    .def("getPos", &Cell::getPos)
    .def_property("radius", &Cell::getRadius, nullptr);

    py::class_<Point, std::shared_ptr<Point>>(m, "Point", py::buffer_protocol())
    .def(py::init<double, double>())
    .def_property("x", &Point::getX, nullptr)
    .def_property("y", &Point::getY, nullptr);
}
