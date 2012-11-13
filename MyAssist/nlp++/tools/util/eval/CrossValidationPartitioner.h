#ifndef CROSSVALIDATIONPARTITIONER
#define CROSSVALIDATIONPARTITIONER

#include "../tools/util/ObjectStream.h"
#include "ObjectStream<E>.h"
#include "E.h"
#include <string>

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreemnets.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace eval
            {


                using opennlp::tools::util::CollectionObjectStream;
                using opennlp::tools::util::ObjectStream;

                /// <summary>
                /// Provides access to training and test partitions for n-fold cross validation.
                /// <p>
                /// Cross validation is used to evaluate the performance of a classifier when only
                /// training data is available. The training set is split into n parts
                /// and the training / evaluation is performed n times on these parts. 
                /// The training partition always consists of n -1 parts and one part is used for testing.
                /// <p>
                /// To use the <code>CrossValidationPartioner</code> a client iterates over the n
                /// <code>TrainingSampleStream</code>s. Each </code>TrainingSampleStream</code> represents
                /// one partition and is used first for training and afterwards for testing.
                /// The <code>TestSampleStream</code> can be obtained from the <code>TrainingSampleStream</code>
                /// with the <code>getTestSampleStream</code> method.
                /// </summary>
                template<typename E>
                class CrossValidationPartitioner
                {

                  /// <summary>
                  /// The <code>TestSampleStream</code> iterates over all test elements.
                  /// </summary>
                  /// @param <E> </param>
              private:
                  template<typename E>
                  class TestSampleStream : public ObjectStream<E>
                  {

                private:
                    ObjectStream<E> *sampleStream;

                    const int numberOfPartitions;

                    const int testIndex;

                    int index;

                    bool isPoisened;

                    TestSampleStream(ObjectStream<E> *sampleStream, int numberOfPartitions, int testIndex) : numberOfPartitions(numberOfPartitions), testIndex(testIndex)
                    {
                      this->sampleStream = sampleStream;
                    }

                public:
                    virtual E read() throw(IOException)
                    {
                      if (isPoisened)
                      {
                        throw IllegalStateException();
                      }

                      // skip training samples
                      while (index % numberOfPartitions != testIndex)
                      {
                        sampleStream->read();
                        index++;
                      }

                      index++;

                      return sampleStream->read();
                    }

                    /// <summary>
                    /// Throws <code>UnsupportedOperationException</code>
                    /// </summary>
                    virtual void reset()
                    {
                      throw UnsupportedOperationException();
                    }

                    virtual void close() throw(IOException)
                    {
                      sampleStream->close();
                      isPoisened = true;
                    }

                    virtual void poison()
                    {
                      isPoisened = true;
                    }
                  };

                  /// <summary>
                  /// The <code>TrainingSampleStream</code> which iterates over
                  /// all training elements.
                  /// 
                  /// Note:
                  /// After the <code>TestSampleStream</code> was obtained
                  /// the <code>TrainingSampleStream</code> must not be used
                  /// anymore, otherwise a <seealso cref="IllegalStateException"/>
                  /// is thrown.
                  /// 
                  /// The <code>ObjectStream></code>s must not be used anymore after the
                  /// <code>CrossValidationPartitioner</code> was moved
                  /// to one of next partitions. If they are called anyway
                  /// a <seealso cref="IllegalStateException"/> is thrown.
                  /// </summary>
                  /// @param <E> </param>
              public:
                  template<typename E>
                  class TrainingSampleStream : public ObjectStream<E>
                  {

                private:
                    ObjectStream<E> *sampleStream;

                    const int numberOfPartitions;

                    const int testIndex;

                    int index;

                    bool isPoisened;

                    TestSampleStream<E> *testSampleStream;

                public:
                    TrainingSampleStream(ObjectStream<E> *sampleStream, int numberOfPartitions, int testIndex) : numberOfPartitions(numberOfPartitions), testIndex(testIndex)
                    {
                      this->sampleStream = sampleStream;
                    }

                    virtual E read() throw(IOException)
                    {

                      if (testSampleStream != 0 || isPoisened)
                      {
                        throw IllegalStateException();
                      }

                      // If the test element is reached skip over it to not include it in
                      // the training data
                      if (index % numberOfPartitions == testIndex)
                      {
                        sampleStream->read();
                        index++;
                      }

                      index++;

                      return sampleStream->read();
                    }

                    /// <summary>
                    /// Throws <code>UnsupportedOperationException</code>
                    /// </summary>
                    virtual void reset()
                    {
                      throw UnsupportedOperationException();
                    }

                    virtual void close() throw(IOException)
                    {
                      sampleStream->close();
                      poison();
                    }

                    virtual void poison()
                    {
                      isPoisened = true;
                      if (testSampleStream != 0)
                        testSampleStream->poison();
                    }

                    /// <summary>
                    /// Retrieves the <code>ObjectStream</code> over the test/evaluations
                    /// elements and poisons this <code>TrainingSampleStream</code>.
                    /// From now on calls to the hasNext and next methods are forbidden
                    /// and will raise an<code>IllegalArgumentException</code>.
                    /// </summary>
                    /// <returns> the test sample stream </returns>
                    virtual ObjectStream<E> *getTestSampleStream() throw(IOException)
                    {

                      if (isPoisened)
                      {
                        throw IllegalStateException();
                      }

                      if (testSampleStream == 0)
                      {

                        sampleStream->reset();
                        testSampleStream = new TestSampleStream<E>(sampleStream, numberOfPartitions, testIndex);
                      }

                      return testSampleStream;
                    }
                  };

                  /// <summary>
                  /// An <code>ObjectStream</code> over the whole set of data samples which
                  /// are used for the cross validation.
                  /// </summary>
              private:
                  ObjectStream<E> *sampleStream;

                  /// <summary>
                  /// The number of parts the data is divided into.
                  /// </summary>
                  const int numberOfPartitions;

                  /// <summary>
                  /// The index of test part.
                  /// </summary>
                  int testIndex;

                  /// <summary>
                  /// The last handed out <code>TrainingIterator</code>. The reference
                  /// is needed to poison the instance to fail fast if it is used
                  /// despite the fact that it is forbidden!.
                  /// </summary>
                  TrainingSampleStream<E> *lastTrainingSampleStream;

                  /// <summary>
                  /// Initializes the current instance.
                  /// </summary>
                  /// <param name="inElements"> </param>
                  /// <param name="numberOfPartitions"> </param>
              public:
                  CrossValidationPartitioner(ObjectStream<E> *inElements, int numberOfPartitions) : numberOfPartitions(numberOfPartitions)
                  {
                    this->sampleStream = inElements;
                  }

                  /// <summary>
                  /// Initializes the current instance.
                  /// </summary>
                  /// <param name="elements"> </param>
                  /// <param name="numberOfPartitions"> </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  CrossValidationPartitioner(Collection<E> *elements, int numberOfPartitions) //this(new CollectionObjectStream<E>(elements), numberOfPartitions);
                  {
                  }

                  /// <summary>
                  /// Checks if there are more partitions available.
                  /// </summary>
                  virtual bool hasNext()
                  {
                    return testIndex < numberOfPartitions;
                  }

                  /// <summary>
                  /// Retrieves the next training and test partitions.
                  /// </summary>
                  virtual TrainingSampleStream<E> *next() throw(IOException)
                  {
                    if (hasNext())
                    {
                      if (lastTrainingSampleStream != 0)
                        lastTrainingSampleStream->poison();

                      sampleStream->reset();

                      TrainingSampleStream<E> *trainingSampleStream = new TrainingSampleStream<E>(sampleStream, numberOfPartitions, testIndex);

                      testIndex++;

                      lastTrainingSampleStream = trainingSampleStream;

                      return trainingSampleStream;
                    }
                    else
                    {
                      throw NoSuchElementException();
                    }
                  }

                  virtual std::string ToString()
                  {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    return "At partition" + int::toString(testIndex + 1) + " of " + int::toString(numberOfPartitions);
                  }
                };

            }
        }
    }
}


#endif	//#ifndef CROSSVALIDATIONPARTITIONER
