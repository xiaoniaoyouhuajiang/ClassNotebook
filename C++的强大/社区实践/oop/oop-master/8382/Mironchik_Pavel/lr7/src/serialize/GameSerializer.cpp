#include <GAME/serialize/GameSerializer.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/log/Log.hpp>
#include <GAME/serialize/FileSigner.hpp>

GameSerializer::GameSerializer(std::string filename) : _filename(filename) {}

void GameSerializer::write(GameBoard* board) {
	try {
		FileSession session(_filename, std::ios::in | std::ios::out | std::ios::binary);
		OutObjectsTable table;
		table.writeInfo(session.fstream(), board);
		board->writeObject(session.fstream(), table);

		FileSigner().makeSign(session.fstream());

		LogInfo logInfo;
		logInfo.name = "GameSerializer:write";
		logInfo.pushParam("status", "success");
		Log::log(logInfo);
	}
	catch (...) {
		LogInfo logInfo;
		logInfo.name = "GameSerializer:write";
		logInfo.pushParam("status", "failed");
		logInfo.pushParam("reason", "exception was thrown");
		Log::log(logInfo);
	}
}

GameBoard* GameSerializer::read() {
	try {
		FileSession session(_filename, std::ios::in | std::ios::binary);

		if (!FileSigner().checkSign(session.fstream())) {
			LogInfo logInfo;
			logInfo.name = "GameSerializer:read";
			logInfo.pushParam("status", "failed");
			logInfo.pushParam("reason", "invalid sign");
			Log::log(logInfo);
			return nullptr;
		}

		InObjectsTable table;
		ObjectInfo info = table.readInfo(session.fstream());
		auto board = new GameBoard(session.fstream(), table);
		table.setObject(info, board);

		LogInfo logInfo;
		logInfo.name = "GameSerializer:read";
		logInfo.pushParam("status", "success");
		Log::log(logInfo);
		return board;
	}
	catch (...) {
		LogInfo logInfo;
		logInfo.name = "GameSerializer:read";
		logInfo.pushParam("status", "failed");
		logInfo.pushParam("reason", "exception was thrown");
		Log::log(logInfo);
		return nullptr;
	}
}