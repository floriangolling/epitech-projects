package com.example.redditech.controllers

import android.content.ContentValues
import android.util.Log
import com.example.redditech.models.UserInfo
import com.example.redditech.oauth.OAuthManager
import okhttp3.Call
import okhttp3.Callback
import okhttp3.Request
import okhttp3.Response
import org.json.JSONException
import org.json.JSONObject
import java.io.IOException
import java.util.concurrent.CountDownLatch

object User {
    fun getClientInfo() {
        val countDownLatch = CountDownLatch(1)

        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Bearer ${OAuthManager.getAccessToken().toString()}")
            .url("https://oauth.reddit.com/api/v1/me")
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
                    UserInfo.setData(data)
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