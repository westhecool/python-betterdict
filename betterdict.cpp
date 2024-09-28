#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <variant>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <any>

namespace py = pybind11;

using pyAny = std::variant<int, long, float, double, std::string, py::str, bool, py::bool_, py::none, py::list, py::tuple, py::dict, py::set, py::bytes, py::function, py::iterator>;

using string = std::variant<std::string, py::str>;

class BetterDict {
public:
    BetterDict() {}
    bool exists(string key) {
        return data.find(key) != data.end();
    }
    void set(string key, pyAny value, bool overwrite = false) {
        if (this->exists(key) && !overwrite) {
            throw py::key_error("Key already exists and overwrite is false");
        } else {
            data[key] = value;
        }
    }
    pyAny get(string key, bool remove = false) {
        if (this->exists(key)) {
            pyAny value = data[key];
            if (remove) {
                this->remove(key);
            }
            return value;
        } else {
            throw py::key_error("Key not found");
        }
    }
    void remove(string key) {
        if (this->exists(key)) {
            data.erase(key);
        } else {
            throw py::key_error("Key not found");
        }
    }
private:
    std::map<string, pyAny> data;
};

PYBIND11_MODULE(betterdict, m) {
     py::class_<BetterDict>(m, "BetterDict")
        // Bind the constructor
        .def(py::init())
        
        // Bind the methods
        .def("exists", &BetterDict::exists, "Checks if a key exists in the dict", py::arg("key"))
        .def("set", &BetterDict::set, "Sets a value in the dict", py::arg("key"), py::arg("value"), py::arg("overwrite") = false)
        .def("get", &BetterDict::get, "Gets a value from the dict", py::arg("key"), py::arg("remove") = false)
        .def("remove", &BetterDict::remove, "Removes a value from the dict", py::arg("key"));
}
