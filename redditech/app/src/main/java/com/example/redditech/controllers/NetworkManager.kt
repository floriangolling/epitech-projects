package com.example.redditech.controllers

import okhttp3.*

object NetworkManager {
    private val client: OkHttpClient = OkHttpClient()

    fun getClient(): OkHttpClient {
        return (client)
    }
}