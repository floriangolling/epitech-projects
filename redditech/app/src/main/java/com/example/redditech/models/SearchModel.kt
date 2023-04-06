package com.example.redditech.models

import org.json.JSONArray
import org.json.JSONObject

object SearchModel {
    private var searchData: JSONObject? = null

    fun setData(json: JSONObject) {
        searchData = json
    }

    fun getData(): JSONArray {
        val data = searchData!!.getJSONObject("data")
        val array = data.getJSONArray("children")
        return (array)
    }
}