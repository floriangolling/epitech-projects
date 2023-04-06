package com.example.redditech.models

import android.annotation.SuppressLint
import android.os.Build
import androidx.annotation.RequiresApi
import org.json.JSONObject
import java.text.SimpleDateFormat
import java.time.format.DateTimeFormatter
import java.time.format.FormatStyle
import java.util.*

object UserInfo {
    private var userData: JSONObject? = null

    fun setData(json: JSONObject) {
        userData = json
    }

    fun getProfilePicture(): String ? {
        return when {
            userData!!.optString("icon_img").contains(".jpg") -> (userData!!.optString("icon_img").substringBefore(".jpg") + ".jpg")
            userData!!.optString("icon_img").contains(".png") -> (userData!!.optString("icon_img").substringBefore(".png") + ".png")
            else -> (userData!!.optString("icon_img"))
        }
    }

    @RequiresApi(Build.VERSION_CODES.O)
    fun getProperty(str: String): String ? {
        when (str) {
            "public_description" -> {
                val data : JSONObject? = userData!!.optJSONObject("subreddit")
                return (data!!.optString("public_description"))
            }
            "subscribers" -> {
                val data : JSONObject? = userData!!.optJSONObject("subreddit")
                return (data!!.optString("subscribers"))
            }
            "created" -> {
                val date = getDateTime(userData!!.optLong("created"))
                date!!.format(DateTimeFormatter.ofLocalizedDate(FormatStyle.FULL))
                return (getDateTime(userData!!.optLong("created")))
            }
            "year" -> {
                val data =  (getDateTime(userData!!.optLong("created"))?.takeLast(4))
                val tsLong = System.currentTimeMillis() / 1000
                val data2 = (getDateTime(tsLong)?.takeLast(4))
                val finale = data2!!.toLong() - data!!.toLong()
                return (finale.toString())
            }
            "display_name" -> {
                val data : JSONObject? = userData!!.optJSONObject("subreddit")
                return (data!!.optString("display_name_prefixed"))
            }
            else -> {
                return (userData!!.optString(str))
            }
        }
    }

    @SuppressLint("SimpleDateFormat")
    private fun getDateTime(s: Long): String? {
        return try {
            val sdf = SimpleDateFormat("MM/dd/yyyy")
            val netDate = Date(s * 1000)
            sdf.format(netDate)
        } catch (e: Exception) {
            e.toString()
        }
    }
}