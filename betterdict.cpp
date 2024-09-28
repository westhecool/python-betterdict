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

class BetterDict {
public:
    BetterDict() {}
    bool includes(pyAny key) {
        return data.find(key) != data.end();
    }
    void set(pyAny key, pyAny value, bool overwrite = false) {
        if (this->includes(key) && !overwrite) {
            throw py::key_error("Key already includes and overwrite is false");
        } else {
            data[key] = value;
        }
    }
    pyAny get(pyAny key, bool remove = false) {
        if (this->includes(key)) {
            pyAny value = data[key];
            if (remove) {
                this->remove(key);
            }
            return value;
        } else {
            throw py::key_error("Key not found");
        }
    }
    void remove(pyAny key) {
        if (this->includes(key)) {
            data.erase(key);
        } else {
            throw py::key_error("Key not found");
        }
    }
    void clear() {
        data.clear();
    }
    int size() {
        return data.size();
    }
private:
    std::map<pyAny, pyAny> data;
};

class BetterDictBinary : public BetterDict {
public:
    void set(pyAny key, py::bytes value, bool overwrite = false) {
        if (this->includes(key) && !overwrite) {
            throw py::key_error("Key already includes and overwrite is false");
        } else {
            data[key] = value;
        }
    }
    py::bytes get(pyAny key, bool remove = false) {
        if (this->includes(key)) {
            py::bytes value = data[key];
            if (remove) {
                this->remove(key);
            }
            return value;
        } else {
            throw py::key_error("Key not found");
        }
    }
private:
    std::map<pyAny, py::bytes> data;
};

PYBIND11_MODULE(betterdict, m) {
     py::class_<BetterDict>(m, "BetterDict")
        // Bind the constructor
        .def(py::init())
        
        // Bind the methods
        .def("includes", &BetterDict::includes, "Checks if a key exists in the dict", py::arg("key"))
        .def("set", &BetterDict::set, "Sets a value in the dict", py::arg("key"), py::arg("value"), py::arg("overwrite") = false)
        .def("get", &BetterDict::get, "Gets a value from the dict", py::arg("key"), py::arg("remove") = false)
        .def("remove", &BetterDict::remove, "Removes a value from the dict and frees memory", py::arg("key"))
        .def("clear", &BetterDict::clear, "Removes all values from the dict and frees memory")
        .def("size", &BetterDict::size, "Returns the number of values in the dict");

    py::class_<BetterDictBinary>(m, "BetterDictBinary")
        // Bind the constructor
        .def(py::init())
        
        // Bind the methods
        .def("includes", &BetterDictBinary::includes, "Checks if a key exists in the dict", py::arg("key"))
        .def("set", &BetterDictBinary::set, "Sets a value in the dict", py::arg("key"), py::arg("value"), py::arg("overwrite") = false)
        .def("get", &BetterDictBinary::get, "Gets a value from the dict", py::arg("key"), py::arg("remove") = false)
        .def("remove", &BetterDictBinary::remove, "Removes a value from the dict and frees memory", py::arg("key"))
        .def("clear", &BetterDictBinary::clear, "Removes all values from the dict and frees memory")
        .def("size", &BetterDictBinary::size, "Returns the number of values in the dict");
}
