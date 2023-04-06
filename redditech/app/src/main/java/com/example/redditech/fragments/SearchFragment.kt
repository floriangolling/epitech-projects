package com.example.redditech.fragments

import android.annotation.SuppressLint
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.core.view.isVisible
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide
import com.example.redditech.R
import com.example.redditech.utils.CustomAdapterSubreddit
import com.example.redditech.utils.DataProvider
import com.example.redditech.utils.SubRedditItems

class SearchFragment : Fragment() {
    private var sAdapter: CustomAdapterSubreddit? = null
    private var data = ArrayList<SubRedditItems>()
    private lateinit var layout: LinearLayoutManager

    @SuppressLint("NotifyDataSetChanged")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val view: View = inflater.inflate(R.layout.fragment_search, container, false)
        val recyclerview = view.findViewById<RecyclerView>(R.id.recyclerview)
        val notFound = view.findViewById<TextView>(R.id.noResultFound)
        val imageNotFound: ImageView = view.findViewById(R.id.imageNotFound)
        val provider = DataProvider.subredditList
        notFound.isVisible = false
        imageNotFound.isVisible = false
        recyclerview.isVisible = true
        recyclerview.layoutManager = LinearLayoutManager(requireContext())
        layout = recyclerview.layoutManager as LinearLayoutManager
        sAdapter = CustomAdapterSubreddit(data)
        recyclerview.adapter = sAdapter
        data.clear()
        if (provider.isEmpty()) {
            recyclerview.isVisible = false
            notFound.isVisible = true
            imageNotFound.isVisible = true
            Glide.with(this)
                .load("https://i.redd.it/hhwmkzqpqzpz.jpg")
                .override(150, 150)
                .fitCenter()
                .into(imageNotFound)
            return view
        }
        for (i in provider)
            data.add(i)
        sAdapter?.setData(data)
        sAdapter?.notifyDataSetChanged()
        layout.scrollToPositionWithOffset(0, 0)
        return view
    }

}