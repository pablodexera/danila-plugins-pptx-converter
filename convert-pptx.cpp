#include "crow_all.h"
#include <fstream>

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/convert-pptx").methods("POST"_method)([](const crow::request& req){
        auto uploadedFile = req.body;

        std::ofstream ofs("/tmp/uploaded.pptx", std::ios::binary);
        ofs.write(uploadedFile.data(), uploadedFile.size());
        ofs.close();

        // TODO: Aspose.Slides logic here
        std::string resultJson = "{\"presentation\": {\"slides\": []}}";

        return crow::response(200, resultJson);
    });

    app.port(8080).multithreaded().run();
}