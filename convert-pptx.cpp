#include "crow_all.h"
#include <fstream>
#include <string>

std::string get_allowed_origin() {
    // During local dev, allow localhost
    const char* env = std::getenv("ENVIRONMENT");
    if (env && std::string(env) == "production") {
        return "https://chat.danila.ai";
    }
    return "http://localhost:3000"; // Local dev
}

int main() {
    crow::SimpleApp app;

    auto allowed_origin = get_allowed_origin();

    // Health check route
    CROW_ROUTE(app, "/").methods("GET"_method)([allowed_origin](){
        crow::response res(200, "Danila Convert-PPTX API is healthy.");
        res.add_header("Access-Control-Allow-Origin", allowed_origin);
        res.add_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });

    // Preflight CORS handler for /convert-pptx
    CROW_ROUTE(app, "/convert-pptx").methods("OPTIONS"_method)([allowed_origin](){
        crow::response res(204);
        res.add_header("Access-Control-Allow-Origin", allowed_origin);
        res.add_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });

    // Main convert route
    CROW_ROUTE(app, "/convert-pptx").methods("POST"_method)([allowed_origin](const crow::request& req){
        auto uploadedFile = req.body;

        std::ofstream ofs("/tmp/uploaded.pptx", std::ios::binary);
        ofs.write(uploadedFile.data(), uploadedFile.size());
        ofs.close();

        // TODO: Aspose.Slides logic here
        std::string resultJson = "{\"presentation\": {\"slides\": []}}";

        crow::response res(200, resultJson);
        res.add_header("Access-Control-Allow-Origin", allowed_origin);
        res.add_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });

    app.port(8080).multithreaded().run();
}
