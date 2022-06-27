/*****************************************************************//**
 * \file   ImageServer.h
 * \brief  画像の読み込み、削除を行うクラスです。
 *
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#include "DxLib.h"
#include "ImageServer.h"

std::unordered_map<std::string, int> ImageServer::_mapGraph;

void ImageServer::Init() {
	_mapGraph.clear();
}

void ImageServer::Release() {
	ClearGraph();
}

void ImageServer::ClearGraph() {
	for (auto&& graph : _mapGraph) {
		DeleteGraph(graph.second);
	}
	_mapGraph.clear();
}

int ImageServer::Find(std::string filename)
{
	auto itr = _mapGraph.find(filename);
	if (itr != _mapGraph.end()) {
		return itr->second;
	}

	return -1;
}

int ImageServer::LoadGraph(std::string filename)
{
	int cg = Find(filename);
	if (cg == -1) {
		cg = ::LoadGraph(filename.c_str());
		_mapGraph[filename] = cg;
	}
	return cg;
}
