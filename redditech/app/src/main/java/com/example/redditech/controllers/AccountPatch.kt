package com.example.redditech.controllers

import android.content.ContentValues
import android.util.Log
import com.example.redditech.oauth.OAuthManager
import okhttp3.*
import okhttp3.MediaType.Companion.toMediaTypeOrNull
import okhttp3.RequestBody.Companion.toRequestBody
import org.json.JSONException
import org.json.JSONObject
import java.io.IOException
import java.util.concurrent.CountDownLatch

object AccountPatch {

    fun enableFollower(value : Boolean) {
        val obj = JSONObject()
        obj.put("enable_followers", value)
        val mediaType = "application/json; charset=utf-8".toMediaTypeOrNull()
        val countDownLatch = CountDownLatch(1)
        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Bearer ${OAuthManager.getAccessToken().toString()}")
            .url("https://oauth.reddit.com/api/v1/me/prefs")
            .patch(obj.toString().toRequestBody(mediaType))
            .build()

        NetworkManager.getClient().newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e(ContentValues.TAG, "ERROR: $e")
                countDownLatch.countDown()
            }

            @Throws(IOException::class)
            override fun onResponse(call: Call, response: Response) {
                try {
                    countDownLatch.countDown()
                } catch (e: JSONException) {
                    e.printStackTrace()
                    countDownLatch.countDown()
                }
            }
        })
        countDownLatch.await()
    }

    fun unsubscribeMail(value : Boolean) {
        val obj = JSONObject()
        obj.put("email_unsubscribe_all", value)
        val mediaType = "application/json; charset=utf-8".toMediaTypeOrNull()
        val countDownLatch = CountDownLatch(1)
        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Bearer ${OAuthManager.getAccessToken().toString()}")
            .url("https://oauth.reddit.com/api/v1/me/prefs")
            .patch(obj.toString().toRequestBody(mediaType))
            .build()

        NetworkManager.getClient().newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e(ContentValues.TAG, "ERROR: $e")
                countDownLatch.countDown()
            }

            @Throws(IOException::class)
            override fun onResponse(call: Call, response: Response) {
                try {
                    countDownLatch.countDown()
                } catch (e: JSONException) {
                    e.printStackTrace()
                    countDownLatch.countDown()
                }
            }
        })
        countDownLatch.await()
    }

    fun showRecommendationGeo(value : Boolean) {
        val obj = JSONObject()
        obj.put("show_location_based_recommendations", value)
        val mediaType = "application/json; charset=utf-8".toMediaTypeOrNull()
        val countDownLatch = CountDownLatch(1)
        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Bearer ${OAuthManager.getAccessToken().toString()}")
            .url("https://oauth.reddit.com/api/v1/me/prefs")
            .patch(obj.toString().toRequestBody(mediaType))
            .build()

        NetworkManager.getClient().newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e(ContentValues.TAG, "ERROR: $e")
                countDownLatch.countDown()
            }

            @Throws(IOException::class)
            override fun onResponse(call: Call, response: Response) {
                try {
                    countDownLatch.countDown()
                } catch (e: JSONException) {
                    e.printStackTrace()
                    countDownLatch.countDown()
                }
            }
        })
        countDownLatch.await()
    }

    fun showPresence(value : Boolean) {
        val obj = JSONObject()
        obj.put("show_presence", value)
        val mediaType = "application/json; charset=utf-8".toMediaTypeOrNull()
        val countDownLatch = CountDownLatch(1)
        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Bearer ${OAuthManager.getAccessToken().toString()}")
            .url("https://oauth.reddit.com/api/v1/me/prefs")
            .patch(obj.toString().toRequestBody(mediaType))
            .build()

        NetworkManager.getClient().newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e(ContentValues.TAG, "ERROR: $e")
                countDownLatch.countDown()
            }

            @Throws(IOException::class)
            override fun onResponse(call: Call, response: Response) {
                try {
                    countDownLatch.countDown()
                } catch (e: JSONException) {
                    e.printStackTrace()
                    countDownLatch.countDown()
                }
            }
        })
        countDownLatch.await()
    }

    fun acceptPms(value : String) {
        val obj = JSONObject()
        obj.put("accept_pms", value)
        val mediaType = "application/json; charset=utf-8".toMediaTypeOrNull()
        val countDownLatch = CountDownLatch(1)
        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Bearer ${OAuthManager.getAccessToken().toString()}")
            .url("https://oauth.reddit.com/api/v1/me/prefs")
            .patch(obj.toString().toRequestBody(mediaType))
            .build()

        NetworkManager.getClient().newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e(ContentValues.TAG, "ERROR: $e")
                countDownLatch.countDown()
            }

            @Throws(IOException::class)
            override fun onResponse(call: Call, response: Response) {
                try {
                    countDownLatch.countDown()
                } catch (e: JSONException) {
                    e.printStackTrace()
                    countDownLatch.countDown()
                }
            }
        })
        countDownLatch.await()
    }

    fun badCommentAutoCollapse(value : String) {
        val obj = JSONObject()
        obj.put("bad_comment_autocollapse", value)
        val mediaType = "application/json; charset=utf-8".toMediaTypeOrNull()
        val countDownLatch = CountDownLatch(1)
        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Bearer ${OAuthManager.getAccessToken().toString()}")
            .url("https://oauth.reddit.com/api/v1/me/prefs")
            .patch(obj.toString().toRequestBody(mediaType))
            .build()

        NetworkManager.getClient().newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e(ContentValues.TAG, "ERROR: $e")
                countDownLatch.countDown()
            }

            @Throws(IOException::class)
            override fun onResponse(call: Call, response: Response) {
                try {
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