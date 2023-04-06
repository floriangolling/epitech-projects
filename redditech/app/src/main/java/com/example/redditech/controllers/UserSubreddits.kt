package com.example.redditech.controllers

import android.content.ContentValues
import android.util.Log
import com.example.redditech.utils.DataProvider
import com.example.redditech.models.UserSubredditsModel
import com.example.redditech.oauth.OAuthManager
import okhttp3.Call
import okhttp3.Callback
import okhttp3.Request
import okhttp3.Response
import org.json.JSONException
import org.json.JSONObject
import java.io.IOException
import java.util.concurrent.CountDownLatch

object UserSubreddits {
    fun getBestPosts(after : String?) {
        val countDownLatch = CountDownLatch(1)
        DataProvider.onPage = "main"

        val url = if (after != null) {
            "https://oauth.reddit.com/best?limit=10&after=$after"
        } else {
            "https://oauth.reddit.com/best?limit=10"
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
                    if (after != null) {
                        UserSubredditsModel.addToBest(data)
                    } else {
                        UserSubredditsModel.setBestData(data)
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

    fun getHotPost(after : String?) {
        val countDownLatch = CountDownLatch(1)
        DataProvider.onPage = "main"

        val url = if (after != null) {
            "https://oauth.reddit.com/hot?limit=10&after=$after"
        } else {
            "https://oauth.reddit.com/hot?limit=10"
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
                    if (after != null) {
                        UserSubredditsModel.addToHot(data)
                    } else {
                        UserSubredditsModel.setHotData(data)
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

    fun getNewPost(after: String?) {
        val countDownLatch = CountDownLatch(1)
        DataProvider.onPage = "main"

        val url = if (after != null) {
            "https://oauth.reddit.com/new?limit=10&after=$after"
        } else {
            "https://oauth.reddit.com/new?limit=10"
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
                    if (after != null) {
                        UserSubredditsModel.addToNew(data)
                    } else {
                        UserSubredditsModel.setNewData(data)
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