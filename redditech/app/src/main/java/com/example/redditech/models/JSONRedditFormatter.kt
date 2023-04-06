package com.example.redditech.models

import com.example.redditech.utils.*
import org.json.JSONArray
import org.json.JSONObject

object JSONRedditFormatter {
    fun formatJson(array: JSONArray) {

        DataProvider.redditList.clear()

        for (i in 0 until array.length()) {
            val item = array.getJSONObject(i)
            val data : JSONObject = item.getJSONObject("data")
            val itemView = ItemsViewModel()

            when {
                data.optString("post_hint") == "image" -> {
                    itemView.cardType = CardTypeEnum.IMAGE
                    itemView.link = data.optString("url")
                    itemView.title = data.optString("title")
                }
                data.optString("post_hint") == "self" -> {
                    itemView.cardType = CardTypeEnum.TEXT
                    itemView.text = data.optString("selftext")
                    itemView.title = data.optString("title")
                }
                (data.optString("post_hint") == "rich:video" || data.optString("post_hint") == "hosted:video") &&
                        data.optString("is_video") == "true" -> {
                    itemView.cardType = CardTypeEnum.VIDEO
                    itemView.title = data.optString("title")
                    if (data.optString("post_hint") == "hosted:video") {
                        val media: JSONObject = data.optJSONObject("media")!!
                        val redditVideo: JSONObject = media.optJSONObject("reddit_video")!!
                        itemView.link = redditVideo.optString("hls_url")
                        itemView.videoType = VideoTypeHost.HOSTED
                    } else {
                        val media: JSONObject = data.optJSONObject("secure_media_embed")!!
                        itemView.link = media.optString("media_domain_url")
                        itemView.videoType = VideoTypeHost.RICH
                    }
                }
                data.optString("post_hint") == "link" -> {
                    itemView.cardType = CardTypeEnum.LINK
                    itemView.link = data.optString("url")
                    itemView.title = data.optString("title")
                }
                (data.optString("post_hint") == "rich:video" || data.optString("post_hint") == "hosted:video") &&
                        data.optString("is_video") == "false" -> {
                    if ((data.optString("post_hint") == "rich:video")) {
                        if (data.optString("domain") == "youtube.com") {
                            itemView.link = data.optString("url")
                            itemView.cardType = CardTypeEnum.LINK
                        } else {
                            val media: JSONObject = data.optJSONObject("media")!!
                            val redditVideo: JSONObject = media.optJSONObject("oembed")!!
                            itemView.link = redditVideo.optString("thumbnail_url")
                            itemView.cardType = CardTypeEnum.GIF
                        }
                    } else {
                        val media: JSONObject = data.optJSONObject("media")!!
                        val redditVideo: JSONObject = media.optJSONObject("reddit_video")!!
                        itemView.link = redditVideo.optString("hls_url")
                        itemView.videoType = VideoTypeHost.HOSTED
                        itemView.cardType = CardTypeEnum.VIDEO
                    }
                    itemView.title = data.optString("title")
                }
                else -> {
                    if (data.optString("self").isNotEmpty()) {
                        itemView.cardType = CardTypeEnum.TEXT
                        itemView.title = data.optString("title")
                    } else {
                        itemView.cardType = CardTypeEnum.EMPTY
                        itemView.title = data.optString("title")
                    }
                }
            }
            itemView.Username = "u/".plus(data.optString("author"))
            itemView.subreddit = data.optString("subreddit_name_prefixed")
            itemView.commentsNumber = (data.optString("num_comments").toInt())
            itemView.likeNumber = (data.optString("score").toInt())
            DataProvider.redditList.add(itemView)
        }
    }

    fun formatSubRedditJSON(array: JSONArray) {

        DataProvider.subredditList.clear()

        for (i in 0 until array.length()) {
            val item = array.getJSONObject(i)
            val data : JSONObject = item.getJSONObject("data")
            val itemView = SubRedditItems()

            itemView.title = data.optString("display_name")
            val url = data.optString("community_icon")
            itemView.image = url.substringBefore("?w")
            itemView.subscribers = Utils.formatSubCount(data.optString("subscribers").toDouble())
            itemView.description = data.optString("public_description")
            itemView.userIsSubscribe = data.optString("user_is_subscriber").toBoolean()
            val banner = data.optString("banner_background_image")
            itemView.subreddit_banner = banner.substringBefore("?w")
            itemView.titleTitle = data.optString("title")
            DataProvider.subredditList.add(itemView)
        }
    }
}
