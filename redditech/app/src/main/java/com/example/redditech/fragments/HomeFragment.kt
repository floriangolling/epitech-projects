package com.example.redditech.fragments

import android.annotation.SuppressLint
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import androidx.core.view.isVisible
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout
import com.example.redditech.utils.CustomAdapter
import com.example.redditech.utils.DataProvider
import com.example.redditech.utils.ItemsViewModel
import com.example.redditech.R
import com.example.redditech.controllers.UserSubreddits
import com.example.redditech.models.JSONRedditFormatter
import com.example.redditech.models.UserSubredditsModel
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch

class HomeFragment : Fragment() {
    private var sAdapter: CustomAdapter? = null
    private var data = ArrayList<ItemsViewModel>()
    private lateinit var layout : LinearLayoutManager
    private lateinit var progressBar : ProgressBar
    private lateinit var swipe : SwipeRefreshLayout

    @SuppressLint("NotifyDataSetChanged")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val view : View =  inflater.inflate(R.layout.fragment_home, container, false)
        val adapter = ArrayAdapter.createFromResource(requireContext(),
            R.array.category_array, android.R.layout.simple_spinner_item)
        val categorySpinner : Spinner = view.findViewById(R.id.category_spinner)
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        categorySpinner.adapter = adapter
        categorySpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            @SuppressLint("NotifyDataSetChanged")
            override fun onItemSelected(adapterView: AdapterView<*>?, view: View, i: Int, l: Long) {
                if (adapterView != null) {
                    progressBar.isVisible = true
                    swipe.isVisible = false
                    val text = adapterView.getItemAtPosition(i).toString()
                    GlobalScope.launch(Dispatchers.IO) {
                        when (text) {
                            "Best" -> {
                                UserSubreddits.getBestPosts(null)
                                JSONRedditFormatter.formatJson(UserSubredditsModel.getBestData())
                                DataProvider.currentlyDisplaying = "Best"
                            }
                            "Hot" -> {
                                UserSubreddits.getHotPost(null)
                                JSONRedditFormatter.formatJson(UserSubredditsModel.getHotData())
                                DataProvider.currentlyDisplaying = "Hot"
                            }
                            "New" -> {
                                UserSubreddits.getNewPost(null)
                                JSONRedditFormatter.formatJson(UserSubredditsModel.getNewData())
                                DataProvider.currentlyDisplaying = "New"
                            }
                        }
                        activity!!.runOnUiThread {
                            data.clear()
                            val provider = DataProvider.redditList
                            for (item in provider) {
                                data.add(item)
                            }
                            sAdapter?.setData(data)
                            sAdapter?.notifyDataSetChanged()
                            swipe.isVisible = true
                            progressBar.isVisible = false
                            layout.scrollToPositionWithOffset(0, 0)
                        }
                    }
                }
            }

            override fun onNothingSelected(adapterView: AdapterView<*>?) {
                return
            }
        }
        progressBar = view.findViewById(R.id.progressBar1)
        val recyclerview = view.findViewById<RecyclerView>(R.id.recyclerview)
        swipe = view.findViewById(R.id.swipeContainer)
        recyclerview.layoutManager = LinearLayoutManager(requireContext())
        layout = recyclerview.layoutManager as LinearLayoutManager
        sAdapter = CustomAdapter(data)
        recyclerview.adapter = sAdapter
        swipe.setOnRefreshListener {
            GlobalScope.launch(Dispatchers.IO) {
                when (categorySpinner.selectedItem.toString()) {
                    "Best" -> {
                        DataProvider.currentlyDisplaying = "Best"
                        UserSubreddits.getBestPosts(null)
                        JSONRedditFormatter.formatJson(UserSubredditsModel.getBestData())
                    }
                    "Hot" -> {
                        DataProvider.currentlyDisplaying = "Hot"
                        UserSubreddits.getHotPost(null)
                        JSONRedditFormatter.formatJson(UserSubredditsModel.getHotData())
                    }
                    "New" -> {
                        DataProvider.currentlyDisplaying = "New"
                        UserSubreddits.getNewPost(null)
                        JSONRedditFormatter.formatJson(UserSubredditsModel.getNewData())
                    }
                }
                requireActivity().runOnUiThread {
                    data.clear()
                    val provider = DataProvider.redditList
                    for (i in provider) {
                        data.add(i)
                    }
                    sAdapter?.setData(data)
                    sAdapter?.notifyDataSetChanged()
                    swipe.isRefreshing = false
                }
            }
        }
        swipe.setColorSchemeResources(R.color.orange_reddit)
        return view
    }

}