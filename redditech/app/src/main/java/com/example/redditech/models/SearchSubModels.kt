package com.example.redditech.models

import com.example.redditech.utils.DataProvider
import org.json.JSONArray
import org.json.JSONObject

object SearchSubModels {
    private var dataHot: JSONObject? = null
    private var dataNew: JSONObject? = null
    private var dataBest: JSONObject? = null

    fun setHotData(json: JSONObject) {
        val data = json.getJSONObject("data")
        DataProvider.afterName = data.optString("after")
        dataHot = json
    }

    fun setBestData(json: JSONObject) {
        val data = json.getJSONObject("data")
        DataProvider.afterName = data.optString("after")
        dataBest = json
    }

    fun setNewData(json: JSONObject) {
        val data = json.getJSONObject("data")
        DataProvider.afterName = data.optString("after")
        dataNew = json
    }

    fun getNewData(): JSONArray {
        val data = dataNew!!.getJSONObject("data")
        val array = data.getJSONArray("children")
        return (array)
    }

    fun getHotData(): JSONArray {
        val data = dataHot!!.getJSONObject("data")
        DataProvider.afterName = data.optString("after")
        val array = data.getJSONArray("children")
        return (array)
    }

    fun getBestData(): JSONArray {
        val data = dataBest!!.getJSONObject("data")
        DataProvider.afterName = data.optString("after")
        val array = data.getJSONArray("children")
        return (array)
    }

    fun addToBest(json: JSONObject) {
        val data = json.getJSONObject("data")
        DataProvider.afterName = data.optString("after")
        val array = data.getJSONArray("children")

        for (i in 0 until array.length()) {
            val item = array.getJSONObject(i)
            val dataBest = this.dataBest!!.getJSONObject("data")
            val arrayBest = dataBest.getJSONArray("children")
            arrayBest.put(item)
        }
    }

    fun addToHot(json: JSONObject) {
        val data = json.getJSONObject("data")
        val array = data.getJSONArray("children")

        for (i in 0 until array.length()) {
            val item = array.getJSONObject(i)
            val dataBest = this.dataHot!!.getJSONObject("data")
            val arrayBest = dataBest.getJSONArray("children")
            arrayBest.put(item)
        }
    }

    fun addToNew(json: JSONObject) {
        val data = json.getJSONObject("data")
        val array = data.getJSONArray("children")

        for (i in 0 until array.length()) {
            val item = array.getJSONObject(i)
            val dataBest = this.dataNew!!.getJSONObject("data")
            val arrayBest = dataBest.getJSONArray("children")
            arrayBest.put(item)
        }
    }
}