package com.example.redditech.utils

object DataProvider {
    var redditList: MutableList<ItemsViewModel> = mutableListOf()
    var subredditList: MutableList<SubRedditItems> = mutableListOf()
    lateinit var subRedditInfo: SubRedditItems
    var currentlyDisplaying: String? = null
    var afterName: String? = null
    var onPage: String? = null
}