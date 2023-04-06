package com.example.redditech.controllers

import android.content.ContentValues
import android.util.Log
import com.example.redditech.utils.DataProvider
import com.example.redditech.models.SearchSubModels
import com.example.redditech.oauth.OAuthManager
import okhttp3.Call
import okhttp3.Callback
import okhttp3.Request
import okhttp3.Response
import org.json.JSONException
import org.json.JSONObject
import java.io.IOException
import java.util.concurrent.CountDownLatch

object SubredditsHotNewBest {
    fun getBestPosts(value: String, after : String?) {
        val countDownLatch = CountDownLatch(1)
        DataProvider.onPage = "sub"

        val url = if (after == null) {
            "https://oauth.reddit.com/r/$value/best?limit=10"
        } else {
            "https://oauth.reddit.com/r/$value/best?limit=10&after=$after"
        }

        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Bearer ${OAuthManager.getAccessToken().toString()}")
            .url(url)
            .build()

        NetworkManager.getClient().newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e(ContentValues.TAG, "ERROR: $e")
                countDownLatch.countDown()
            }

            @Throws(IOException::class)
            override fun onResponse(call: Call, response: Response) {
                val json = response.body!!.string()
                try {
                    val data = JSONObject(json)
                    if (after == null) {
                        SearchSubModels.setBestData(data)
                    } else {
                        SearchSubModels.addToBest(data)
                    }
                    countDownLatch.countDown()
                } catch (e: JSONException) {
                    e.printStackTrace()
                    countDownLatch.countDown()
                }
            }
        })
        countDownLatch.await()
    }

    fun getHotPosts(value: String, after: String?) {
        val countDownLatch = CountDownLatch(1)
        DataProvider.onPage = "sub"

        val url = if (after == null) {
            "https://oauth.reddit.com/r/$value/hot?limit=10"
        } else {
            "https://oauth.reddit.com/r/$value/hot?limit=10&after=$after"
        }

        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Bearer ${OAuthManager.getAccessToken().toString()}")
            .url(url)
            .build()

        NetworkManager.getClient().newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e(ContentValues.TAG, "ERROR: $e")
                countDownLatch.countDown()
            }

            @Throws(IOException::class)
            override fun onResponse(call: Call, response: Response) {
                val json = response.body!!.string()
                try {
                    val data = JSONObject(json)
                    if (after == null) {
                        SearchSubModels.setHotData(data)
                    } else {
                        SearchSubModels.addToHot(data)
                    }
                    countDownLatch.countDown()
                } catch (e: JSONException) {
                    e.printStackTrace()
                    countDownLatch.countDown()
                }
            }
        })
        countDownLatch.await()
    }

    fun getNewPosts(value: String, after: String?) {
        val countDownLatch = CountDownLatch(1)
        DataProvider.onPage = "sub"

        val url = if (after == null) {
            "https://oauth.reddit.com/r/$value/new?limit=10"
        } else {
            "https://oauth.reddit.com/r/$value/new?limit=10&after=$after"
        }

        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Bearer ${OAuthManager.getAccessToken().toString()}")
            .url(url)
            .build()

        NetworkManager.getClient().newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e(ContentValues.TAG, "ERROR: $e")
                countDownLatch.countDown()
            }

            @Throws(IOException::class)
            override fun onResponse(call: Call, response: Response) {
                val json = response.body!!.string()
                try {
                    val data = JSONObject(json)
                    if (after == null) {
                        SearchSubModels.setNewData(data)
                    } else {
                        SearchSubModels.addToNew(data)
                    }
                    countDownLatch.countDown()
                } catch (e: JSONException) {
                    e.printStackTrace()
                    countDownLatch.countDown()
                }
            }
        })
        countDownLatch.await()
    }
}