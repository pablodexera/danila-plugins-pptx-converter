#include "crow_all.h"
#include <fstream>

int main() {
    crow::SimpleApp app;

    // Health check route
    CROW_ROUTE(app, "/").methods("GET"_method)([](){
        crow::response res(200, "Danila Convert-PPTX API is healthy.");
        res.add_header("Access-Control-Allow-Origin", "*"); // TEMPORARY - replace later with "https://chat.danila.ai"
        res.add_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });

    // Preflight CORS handler for /convert-pptx
    CROW_ROUTE(app, "/convert-pptx").methods("OPTIONS"_method)([](){
        crow::response res(204); // No Content
        res.add_header("Access-Control-Allow-Origin", "*"); // TEMPORARY - replace later with "https://chat.danila.ai"
        res.add_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });

    // Main convert route
    CROW_ROUTE(app, "/convert-pptx").methods("POST"_method)([](const crow::request& req){
        auto uploadedFile = req.body;

        std::ofstream ofs("/tmp/uploaded.pptx", std::ios::binary);
        ofs.write(uploadedFile.data(), uploadedFile.size());
        ofs.close();

        // TODO: Aspose.Slides logic here
        std::string resultJson = "{\"presentation\": {\"slides\": []}}";

        crow::response res(200, resultJson);
        res.add_header("Access-Control-Allow-Origin", "*"); // TEMPORARY - replace later with "https://chat.danila.ai"
        res.add_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });

    app.port(8080).multithreaded().run();
}